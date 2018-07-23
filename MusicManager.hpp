//
//  MusicManager.hpp
//  Music Manager
//
//  Created by Paul Valdez on 7/22/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#ifndef MusicManager_hpp
#define MusicManager_hpp

#include "SongList.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "SongList.hpp"
#include "Disc.hpp"
#include <time.h>

class MusicManager
{
public:
    // Constructor
    MusicManager(std::string newSongFileName = "musicPlayList.csv");
    //Destructor
    ~MusicManager();
    
    void runProgram();
    
private:
    std::string songFileName;
    
};

#endif /* MusicManager_hpp */
