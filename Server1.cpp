#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <string>

#pragma coment(lib, "ws2_32.lib")
#define PORT 6000

using std::cout;
using std::cin;
using std::string;
using std::endl;
//int sendto(SOCKET s, const char FAR *buf, int len, int flags, const struct sockaddr FAR *to, int tolen);
int main(int argc, char* argv[])
{
	//initialize the network environment
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "WSAStartup failed" << endl;
		return -1;
	}

	//creating a UDP socket
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == SOCKET_ERROR)
	{
		cout << "Socket create failed" << endl;
		return -1;
	}

	//binding info
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(s, (sockaddr *)&serverAddr, sizeof(sockaddr));



	char buf[512];
	while (TRUE)
	{
		memset(buf, 0, 512);
		//Network Node, store the information from the client
		sockaddr_in clientAddr;
		memset(&clientAddr, 0, sizeof(sockaddr_in));

		int clientAddrLen = sizeof(sockaddr);

		//receiving client info
		int ret = recvfrom(s, buf, 512, 0, (sockaddr*)&clientAddr, &clientAddrLen);
		//The inet_ntoa() function converts the Internet host address in, given in network byte order, 
		//to a string in IPv4 dotted-decimal notation. The string is returned in a statically allocated buffer, 
		//which subsequent calls will overwrite.

		//The ntohs() function translates a short integer from network byte order to host byte order.
		cout << "Receive msg: " << buf << "from IP: " << inet_ntoa(clientAddr.sin_addr) << "Port: " << ntohs(clientAddr.sin_port) << endl;
		sendto(s, "Hello World!", strlen("Hello World!"), 0, (sockaddr*)&clientAddr, clientAddrLen);
		cout << "Send msg back to IP: " << inet_ntoa(clientAddr.sin_addr) << "Port: " << ntohs(clientAddr.sin_port) << endl;

	}
	return 0;
}