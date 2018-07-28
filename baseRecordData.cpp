//
//  baseRecordData.cpp
//  Music Manager
//
//  Created by Paul Valdez on 7/20/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#include "baseRecordData.hpp"

//Constructor
BaseRecordData::BaseRecordData()
{
    this -> mArtist = "";
    this -> mAlbumTitle = "";
    this -> mSongTitle = "";
    this -> mGenre = "";
    this -> mSongFileName = "";
    this -> mRating = 0;
    this -> mNumTimesPlayed = 0;
    this -> mSongLength.minutes = 0;
    this -> mSongLength.seconds = 0;
    this -> mSongText = "";
    //Set the tags?
    
}
//Constructor
BaseRecordData::BaseRecordData(std::string &fileData)
{
    parseData(fileData);
}
//Private functions
void BaseRecordData::parseData(std::string &fileData)
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
    
    //Gets the file name
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    this -> mSongFileName = current;
    start = end + 1;
    
    //Set song text
    this -> mSongText = this -> mArtist + " " + this -> mAlbumTitle + " " + this -> mSongTitle + " " +
    this -> mGenre;
    //Gets the file name
    end = fileData.find(",", start);
    current = fileData.substr(start, end - start);
    fileData = current;
}
//Copy constructor
BaseRecordData::BaseRecordData(BaseRecordData &copy)
{
    //Should actually go through one by one and set these
    this -> mArtist = copy.getArtist();
    this -> mAlbumTitle = copy.getAlbum();
    this -> mSongTitle = copy.getSongTitle();
    this -> mGenre = copy.getGenre();
    this -> mSongFileName = copy.getSongFileName();
    this -> mRating = copy.getRating();
    this -> mNumTimesPlayed = copy.getTimesPlayed();
    this -> mSongLength.minutes = copy.getSongLength().minutes;
    this -> mSongLength.seconds = copy.getSongLength().seconds;
    this -> mSongText = copy.getSongText();
}
//Destructor
BaseRecordData::~BaseRecordData()
{
    //For some reason it calls the destructor when initializing????
    //std::cout << "Inside base record data" << std::endl;
}

//Setters and getters ~ should we pass these in as references? I dont think we need to
void BaseRecordData::setArtist(const std::string newArtist)
{
    this -> mArtist = newArtist;
}
void BaseRecordData::setAlbum(const std::string newAlbum)
{
    this -> mAlbumTitle = newAlbum;
}
void BaseRecordData::setSongTitle(const std::string newSongTitle)
{
    this -> mSongTitle = newSongTitle;
}
void BaseRecordData::setGenre(const std::string newGenre)
{
    this -> mGenre = newGenre;
}
void BaseRecordData::setSongFileName(const std::string newSongFileName)
{
    this -> mSongFileName = newSongFileName;
}
void BaseRecordData::setSongLength(const Duration newSongLength)
{
    this -> mSongLength.minutes = newSongLength.minutes;
    this -> mSongLength.seconds = newSongLength.seconds;
}
//Need an update for this as well
void BaseRecordData::setTimesPlayed(const int newTimesPlayed)
{
    this -> mNumTimesPlayed = newTimesPlayed;
}
void BaseRecordData::updateTimesPlayed()
{
    (this -> mNumTimesPlayed)++;
}
void BaseRecordData::setRating(const int newRating)
{
    this -> mRating = newRating;
}

std::string BaseRecordData::getArtist() const
{
    return this -> mArtist;
}
std::string BaseRecordData::getAlbum() const
{
    return this -> mAlbumTitle;
}
std::string BaseRecordData::getSongTitle() const
{
    return this -> mSongTitle;
}
std::string BaseRecordData::getGenre() const
{
    return this -> mGenre;
}
std::string BaseRecordData::getSongFileName() const
{
    return this -> mSongFileName;
}
Duration BaseRecordData::getSongLength() const
{
    return (this -> mSongLength);
}
int BaseRecordData::getTimesPlayed() const
{
    return  this -> mNumTimesPlayed;
}
int BaseRecordData::getRating() const
{
    return  this -> mRating;
}
//Operators
BaseRecordData & BaseRecordData::operator =(BaseRecordData &rhs)
{
    //Set everything up
    this -> mArtist = rhs.getArtist();
    this -> mAlbumTitle = rhs.getAlbum();
    this -> mSongTitle = rhs.getSongTitle();
    this -> mGenre = rhs.getGenre();
    this -> mNumTimesPlayed = rhs.getTimesPlayed();
    this -> mRating = rhs.getRating();
    this -> mSongFileName = rhs.getSongFileName();
    //Because duration is a struct, we cant just set it equal. We have to set each thing in the struct
    this -> mSongLength.minutes = rhs.getSongLength().minutes;
    this -> mSongLength.seconds = rhs.getSongLength().seconds;
    this -> mSongText = rhs.getSongText();
    //Return the data
    return (*this);
}

bool BaseRecordData::operator == (BaseRecordData &rhs)
{
    return (this -> mSongText == rhs.getSongText());
}

std::string BaseRecordData::getSongText() const
{
    return this -> mSongText;
}
void BaseRecordData::setSongText(const std::string newSongText)
{
    this -> mSongText =  newSongText;
}


