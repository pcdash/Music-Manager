//
//  SongList.cpp
//  Music Manager
//
//  Created by Paul Valdez on 7/20/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#include "SongList.hpp"

SongList::SongList()
{
    this -> mpList = nullptr;
    
    //Sets the random color list
    (this -> randomColors)[0] = sf::Color::Red;
    //(this -> randomColors)[1] = sf::Color::Blue;
    (this -> randomColors)[1] = sf::Color::Yellow;
    (this -> randomColors)[2] = sf::Color::Green;
    (this -> randomColors)[3] = sf::Color::Magenta;
    (this -> randomColors)[4] = sf::Color::Black;
}

//insert
void SongList::buildList(std::string fileName)
{
    std::string tempSongData = "";
    (this -> songFile).open(fileName);
    if (songFile.is_open())
    {
        //Read from file and populate list
        while (!songFile.eof())
        {
            getline(songFile, tempSongData);
            insertHelper(tempSongData);
        }
        songFile.close();
    }
    else
    {
        std::cout << "file was not opened" << std::endl;
        throw ("File was not opened");
    }
}

//insert helper
void SongList::insertHelper(std::string songData)
{
    //Data is actually available
    if (songData != "")
    {
        //Make data with base record
        //Make data with nonbase record
        RecordData tempRecord(songData);
        //Make a new temp node
        Node<RecordData> *pMem = new Node<RecordData>(tempRecord), *pTemp = nullptr, *pLast = nullptr;
        //Check to see if data was actually allocated
        if (pMem != nullptr)
        {
            //Check to see if the list is empty
            if (this -> mpList == nullptr)
            {
                //Set the previous and the next
                this -> mpList = pMem;
                (this -> mpList) -> setNext(pMem);
                (this -> mpList) -> setPrev(pMem);
            }
            else //Inserts at front
            {
                // Set the last node
                pLast = (this -> mpList) -> getPrev();
                pLast -> setNext(pMem);
                pMem -> setPrev(pLast);
                // Set the first node
                pMem -> setNext(mpList);
                (this -> mpList) -> setPrev(pMem);
                //Do I need this? I dont think so not really but its not insert at front if so. Its insert at back
                //this -> mpList = pMem;
            }
        }
        
    }
}

SongList::~SongList()
{
    //Calls destructor
    //Breaks the circular list
    ((this -> mpList) -> getPrev()) -> setNext(nullptr);
    destroySongList(this -> mpList);
}

//Helper Functions
void SongList::destroySongList(Node<RecordData> * pList)
{
    //List is circular
    if (pList != nullptr)
    {
        destroySongList(pList -> getNext());
        delete pList;
    }
}

Node<RecordData> * SongList::getHead()
{
    return this -> mpList;
}

void SongList::setSongText(RecordData &pSong, sf::Text &ptext, sf::Font &font)
{
    (ptext).setString(pSong.getSongText());
    (ptext).setFont(font);
    (ptext).setFillColor(this -> randomColors[rand() % 5]);
    (ptext).setOutlineColor(this -> randomColors[rand() % 5]);
}


void SongList::play(sf::Texture &texture, sf::Music &music, sf::Text &text, sf::Font &font, bool playPrev)
{
    if (playPrev){
        this -> mpList = (this -> mpList) -> getPrev();
    }
    // Load a texture to display
    if (!texture.loadFromFile(/*resourcePath() + */((this -> mpList) -> getData()).getAlbumCover())) {
        return EXIT_FAILURE;
    }
    if (!font.loadFromFile(/*resourcePath() + */"sansation.ttf")) {
        return EXIT_FAILURE;
    }
    if (!music.openFromFile(/*resourcePath() + */((this -> mpList) -> getData()).getSongFileName())){
        return EXIT_FAILURE;
    }
    setSongText(((this -> mpList) -> getData()), text, font);
    //this -> mpList = (this -> mpList) -> getNext();
}

void SongList::updateWhichSong(void){
    this -> mpList = (this -> mpList) -> getNext();
}



















