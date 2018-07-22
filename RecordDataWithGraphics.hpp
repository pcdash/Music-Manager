//
//  RecordDataWithGraphics.hpp
//  Music Manager
//
//  Created by Paul Valdez on 7/20/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#ifndef RecordDataWithGraphics_hpp
#define RecordDataWithGraphics_hpp

#include "baseRecordData.hpp"

class RecordData : public BaseRecordData
{
public:
    //default constructor
    RecordData();
    //Constructor
    RecordData(std::string fileData);
    //Copy constructor
    RecordData(RecordData &copy);
    //Destructor
    ~RecordData();
    
    //Setters and getters
    // Can inherit most?
    void setAlbumCover(std::string newAlbumCover);
    std::string getAlbumCover();
private:
    std::string mAlbumCover;
    void parseData(std::string fileData);
};

#endif /* RecordDataWithGraphics_hpp */
