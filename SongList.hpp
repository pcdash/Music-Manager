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
#include "baseRecordData.hpp"
//Includes baseRecordData here
//#include "RecordDataWithGraphics.hpp"
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
    Node<BaseRecordData> * getHead();
    void playList(sf::RenderWindow &window);
    
private:
    //Pointer to front
    Node<BaseRecordData> * mpList;
    
    //Could pass these in from main
    fstream songFile;
    
    //Windows
    sf::Text text;
    sf::Font font;
    sf::Color randomColors[5];
    sf::Music music;
    
    //Helper Functions
    void destroySongList(Node<BaseRecordData> * pList);
    void setSongText(BaseRecordData pSong);
    void setSongText(BaseRecordData pSong, sf::Text &ptext);
};

#endif /* SongList_hpp */
