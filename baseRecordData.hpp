//
//  baseRecordData.hpp
//  Music Manager
//
//  Created by Paul Valdez on 7/20/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#ifndef baseRecordData_hpp
#define baseRecordData_hpp

#include <iostream>
#include <string>

//Make the struct to keep the time
typedef struct duration
{
    int minutes;
    int seconds;
} Duration;

class BaseRecordData
{
public:
    //Default Constructor
    BaseRecordData();
    //Constructor
    BaseRecordData(std::string &fileData);
    //Copy constructor
    BaseRecordData(BaseRecordData &copy);
    //Destructor
    ~BaseRecordData();
    
    //Setters and getters ~ should we pass these in as references? I dont think we need to
    void setArtist(const std::string newArtist);
    void setAlbum(const std::string newAlbum);
    void setSongTitle(const std::string newSongTitle);
    void setGenre(const std::string newGenre);
    void setSongFileName(const std::string newSongFileName);
    void setSongLength(const Duration newSongLength);
    //Need an update for this as well
    void setTimesPlayed(const int newTimesPlayed);
    void updateTimesPlayed();
    void setRating(const int newRating);
    void setSongText(const std::string newSongText);
    
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getSongTitle() const;
    std::string getGenre() const;
    std::string getSongFileName() const;
    std::string getSongText() const;
    
    Duration getSongLength() const;
    int getTimesPlayed() const;
    int getRating() const;
    
    //Need to add setters and getters for the tags as well
    
    //Equal operator
    virtual BaseRecordData & operator =(BaseRecordData &rhs);
    bool operator == (BaseRecordData &rhs);
    //Display record ~ How would we do this?
    //virtual void displayRecord();
protected:
    //Can we just have them as strings?
    std::string mArtist;
    std::string mAlbumTitle;
    std::string mSongTitle;
    std::string mGenre;
    std::string mSongFileName;
    std::string mSongText;
    
    Duration mSongLength;
    int mNumTimesPlayed;
    int mRating;
    
    //Need a set of tags?
    
    //Private functions
    void parseData(std::string &fileData);
};


#endif /* baseRecordData_hpp */
