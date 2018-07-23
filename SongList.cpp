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
    (this -> randomColors)[1] = sf::Color::Blue;
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
        BaseRecordData tempRecord(songData);
        //Make a new temp node
        Node<BaseRecordData> *pMem = new Node<BaseRecordData>(tempRecord), *pTemp = nullptr, *pLast = nullptr;
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
void SongList::destroySongList(Node<BaseRecordData> * pList)
{
    //List is circular
    if (pList != nullptr)
    {
        destroySongList(pList -> getNext());
        delete pList;
    }
}

Node<BaseRecordData> * SongList::getHead()
{
    return this -> mpList;
}


//Play the list??
bool SongList::playList(sf::RenderWindow &window)
{
    //Initialize the base data
    Node<BaseRecordData> *pCurSong = this -> mpList, *pLast = this -> mpList;
    bool listPlayed = false,
    songEnded = false,
    playListEnded = false,
    songPaused = false,
    songSkipped = false;
    int songLength = 0;
    // Load the font
    if (!font.loadFromFile("sansation.ttf")){
        return EXIT_FAILURE;
    }
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    //Run while the window is open
    while (window.isOpen() && !playListEnded){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }
            // Pause the song
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                music.pause();
                std::cout << "Music Paused" << std::endl;
                songPaused = true;
            }
            // Play the song if paused
            if ((songPaused) && (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)) {
                music.play();
                std::cout << "Music unpaused" << std::endl;
                songPaused = false;
            }
            //Skip the  next song? Maybe should do with mouse clicks instead
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                //Stop the current music
                music.stop();
                //Move to the next node
                //pCurSong = pCurSong -> getNext();
                std::cout << "Song skipped" << std::endl;
                songSkipped = true;
            }
            //Replay the song?

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                pCurSong = pCurSong -> getPrev();
                //stop the music
                music.stop();
                //Reset the marker to tell the end of the list
                if (pCurSong == pLast && listPlayed)
                {
                    listPlayed = false;
                }
                songSkipped = true;
                std::cout << "get previous song" << std::endl;
            }
            //How to stop and go back to main menu??
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                playListEnded = true;
                music.stop();
            }
            
        }
        //If the music is ended get the next song
        if (!playListEnded && music.getStatus() == sf::Music::Status::Stopped){
            //Get next song?
            if (pCurSong != nullptr)
            {
                if (!(pCurSong -> getData() == pLast -> getData()) || !listPlayed)
                {
                    (pCurSong -> getData()).updateTimesPlayed();
                    //setSongText(pCurSong -> getData(), songText);
                    setSongText(pCurSong -> getData());
                    //Check if the music file was already opened
                    //if (music.getStatus())
                    if (!(music).openFromFile((pCurSong -> getData()).getSongFileName()))
                    {
                        return EXIT_FAILURE;
                    }
                    songLength = (int) music.getDuration().asSeconds() % 500;
                    listPlayed = true;
                    pCurSong = pCurSong -> getNext();
                } else{
                    playListEnded = true;
                }
            }
            //Update song skipped
            songSkipped = false;
            //music.play();
        }
        
        //Play the music
        //if (!songPaused && music.getStatus() == sf::Music::Status::Stopped)
        if (!playListEnded && music.getStatus() == sf::Music::Status::Stopped)
        {
            // Play the music
            music.play();
            std::cout << "Play music" << std::endl;
        }
        if ((int) music.getDuration().asSeconds() % 500 == (int) songLength){
            //Move text
            text.setPosition(text.getPosition().x + .1, text.getPosition().y);
        }
        if (text.getPosition().x > window.getSize().x){
            text.setPosition(0, text.getPosition().y);
        }
        //Clear the window
        window.clear();
        
        //Display the sprite
        window.draw(sprite);
        
        //Display the text
        window.draw(text);
        
        //Update the window
        window.display();
    }
}

void SongList::setSongText(BaseRecordData pSong)
{
    //(this -> text).setString(pSong.getArtist() + " " + pSong.getAlbum() + " " + pSong.get)
    (this -> text).setString(pSong.getSongText());
    (this -> text).setFont(font);
    (this -> text).setFillColor(this -> randomColors[rand() % 5]);
    //Should have default character size of 30?
}

void SongList::setSongText(BaseRecordData pSong, sf::Text &ptext)
{
    (ptext).setString(pSong.getSongText());
    (ptext).setFont(font);
    (ptext).setFillColor(this -> randomColors[rand() % 5]);
}






















