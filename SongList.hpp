//
//  SongList.hpp
//  Music Manager
//
//  Created by Paul Valdez on 7/20/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#ifndef SongList_hpp
#define SongList_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Node.hpp"
//#include "RecordData.hpp"
//Includes RecordData here
#include "RecordDataWithGraphics.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "ResourcePath.hpp"

using std::fstream;

class SongList
{
public:
    //Should only be called with an open file, whereupon it should populate the list upon instantiation
    SongList();
    //Destructor
    ~SongList();
    
    //insert
    void buildList(std::string fileName);
    void insertHelper(std::string songData);
    //Setters and getters
    Node<RecordData> * getHead();
    void playList(sf::RenderWindow &window);
    void play(sf::Texture &texture, sf::Music &music, sf::Text &text, sf::Font &font, bool playPrev);
    void updateWhichSong(void);
private:
    //Pointer to front
    Node<RecordData> * mpList;
    
    //Could pass these in from main
    fstream songFile;
    
    //Windows
    sf::Text text;
    sf::Font font;
    sf::Color randomColors[5];
    sf::Music music;
    
    //Helper Functions
    void destroySongList(Node<RecordData> * pList);
    void setSongText(RecordData pSong);
    //void setSongText(RecordData pSong, sf::Text &ptext);
    void setSongText(RecordData &pSong, sf::Text &ptext, sf::Font &font);
};

#endif /* SongList_hpp */
