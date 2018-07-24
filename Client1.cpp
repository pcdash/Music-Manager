#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#define  PORT 6000
using std::cin;
using std::cout;
using std::string;
using std::endl;
//int recvfrom(SOCKET s, char FAR* buf, int len, int flags, struct sockaddr FAR *from, int FAR *fromlen);
int main(int argc, char* argv[])
{
	//initializing network environment
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "WSAStartup failed" << endl;
		return -1;
	}
	//creating UDP socket
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockClient == INVALID_SOCKET)
	{
		cout << "create socket failed" << endl;
		return -1;
	}
	//declare a structure
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	char buf[] = "client test!";
	//send data
	int dwSent = sendto(sockClient, buf, strlen(buf), 0, (SOCKADDR *)&addr, sizeof(SOCKADDR));
	if (dwSent == 0)
	{
		cout << "send %s failed" << buf << endl;
		return -1;
	}
	cout << "send msg:%s" << buf << endl;

	char recvBuf[512];
	memset(recvBuf, 0, 512);

	sockaddr_in addrSever = { 0 };
	int nServerAddrLen = sizeof(sockaddr_in);
	// receive data
	int dwRecv = recvfrom(sockClient, recvBuf, 512, 0, (SOCKADDR *)&addrSever, &nServerAddrLen);
	cout << "Recv msg from server" << recvBuf << endl;
	//close socket
	closesocket(sockClient);
	//clean up
	WSACleanup();
	system("pause");
	return 0;
}
