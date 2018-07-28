//
//  RecordDataWithGraphics.cpp
//  Music Manager
//
//  Created by Paul Valdez on 7/20/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#include "RecordDataWithGraphics.hpp"

//default constructor
RecordData::RecordData() : BaseRecordData()
{
    this -> mAlbumCover = "";
}
//Constructor
RecordData::RecordData(std::string fileData) : BaseRecordData(fileData)
{
    this -> mAlbumCover = fileData;
    //parseData(fileData);
}
//Copy constructor
RecordData::RecordData(RecordData &copy) : BaseRecordData(copy)
{
    this -> mAlbumCover = copy.getAlbumCover();
}
//Destructor
RecordData::~RecordData()
{
    //std::cout << "Inside RecordData destructor" << std::endl;
}

//Setters and getters
// Can inherit most?
void RecordData::setAlbumCover(std::string newAlbumCover)
{
    this -> mAlbumCover = newAlbumCover;
}
std::string RecordData::getAlbumCover()
{
    return this -> mAlbumCover;
}

void RecordData::parseData(std::string fileData)
{
    unsigned long int start = 0, end = 0;
    std::string current = "", first = "", last = "";
    //First get the name of the artist, this checks if the artist has two names
    if (fileData.at(0) == '"')
    {
        end = fileData.find(",", start++);
        last = fileData.substr(start, end - start);
        start = end + 1;
        end = fileData.find(",", start);
        first = fileData.substr(start, end - start - 1);
        //Puts the first and last name back together
        current = first + " " + last;
        start = end + 1;
    } else{
        end = fileData.find(",", start);
        current = fileData.substr(start, end - start);
        start = end + 1;
    }
    //Set the artist
    this -> mArtist = current;
    
    //Get the album
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mAlbumTitle = current;
    start = end + 1;
    //Get the song name
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mSongTitle = current;
    start = end + 1;
    
    //Get the genre
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mGenre = current;
    start = end + 1;
    
    //Get the length
    end = fileData.find(":", start);
    current = fileData.substr(start, end - start);
    this -> mSongLength.minutes = stoi(current);
    start = end + 1;
    //Gets the seconds
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mSongLength.seconds = stoi(current);
    start = end + 1;
    
    //Gets the rating
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mRating = stoi(current);
    start = end + 1;
    
    //Gets the times played
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mNumTimesPlayed = stoi(current);
    start = end + 1;
    
    //Gets the song file name
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mSongFileName = current;
    start = end + 1;
    
    //Gets the graphic file name
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mAlbumCover = current;
}
