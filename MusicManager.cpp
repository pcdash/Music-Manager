//
//  MusicManager.cpp
//  Music Manager
//
//  Created by Paul Valdez on 7/22/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#include "MusicManager.hpp"

// Constructor
MusicManager::MusicManager(std::string newSongFileName)
{
    this -> songFileName = newSongFileName;
}
//Destructor
MusicManager::~MusicManager(){
    //Music Manager destructor
}
//Runs program
void MusicManager::runProgram()
{
    auto songPosition = sf::seconds(0);
    sf::Text displayMenu;
    unsigned int frameRate = 60;
    bool playMusic = false,
    playPrevious = false,
    skipBackwards = false,
    getCurrentTimeOfSong = false,
    changedSize = false,
    changeVolume = false;
    int song = 0;
    int songLength = 0;
    std::string totalSongLength = "     ---------------------------------------- ";
    sf::Time displaySongPosition;
    SongList musicPlayList;
    musicPlayList.buildList(resourcePath() + "musicPlayList.csv");
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    //window.setFramerateLimit(frameRate);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::Music music;
    sf::Font font;
    sf::Texture mainTexture;
    if (!mainTexture.loadFromFile(resourcePath() + "IMG_3017.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Texture songTexture;
    displayMenu.setFont(font);
    displayMenu.setCharacterSize(20);
    //displayMenu.setString("HAPPY THOUGHTS PRODUCTIONS BRINGS YOU\n                          MUSIC MANAGER\n                                         BY\n                     Chris - Fluffy Dog Owner\n                         Will - EEEEEEEEE = 0\n                      Allison - Busted Function\n                          Paul - The Monster");
    displayMenu.setString("HAPPY THOUGHTS PRODUCTIONS BRINGS YOU\n\t\t\t\t\t\t\t MUSIC MANAGER\n\t\t\t\t\t\t\t\t\t\t\tBY\n\t\t\t\t\t\tChris - Fluffy Dog Owner\n\t\t\t\t\t\t  Will - EEEEEEEEE = 0\n\t\t\t\t\t\tAllison - Busted Function\n\t\t\t\t\t\t     Paul - The Monster");
    displayMenu.setFillColor(*(new sf::Color(sf::Color::Yellow)));
    displayMenu.setPosition(150, 200);
    sf::Text text, timeOfSong, totalTimeOfSong;
    sf::Transform transform;
    musicPlayList.play(songTexture, music, text, font, playPrevious);
    totalTimeOfSong.setFont(font);
    timeOfSong.setFont(font);
    totalTimeOfSong.setFillColor(*(new sf::Color(sf::Color::Red)));
    timeOfSong.setFillColor(*(new sf::Color(sf::Color::Red)));
    //Make a loading sign
    sf::Text loadingCD;
    loadingCD.setFont(font);
    loadingCD.setString("LOADING...");
    loadingCD.setCharacterSize(50);
    loadingCD.setFillColor(*(new sf::Color(sf::Color::Red)));

    loadingCD.setPosition(text.getPosition().x + 300, text.getPosition().y + 300);
    timeOfSong.setPosition(text.getPosition().x + 150, text.getPosition().y + 520);
    totalTimeOfSong.setPosition(text.getPosition().x + 150, text.getPosition().y + 550);
    sf::Sprite mainSprite(mainTexture);
    
    //sf::Sprite musicAlbumSprite(songTexture);
    //mainSprite.setColor(sf::Color::Blue);
    Disc cdShape(175, 40, *(new sf::Vector2f(window.getSize().x/4, window.getSize().y/5)), &songTexture);
    Disc innerCutout(15, 35, *(new sf::Vector2f(cdShape.getPosition().x + cdShape.getRadius() - 15, cdShape.getPosition().y + cdShape.getRadius() - 15)), *(new sf::Color(sf::Color::Black)));
    
    // Play the music
    //music.play();
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved && music.getStatus() == sf::Music::Playing){
                getCurrentTimeOfSong = true;
                displaySongPosition = music.getPlayingOffset();
                timeOfSong.setString(getCurrentTime(music) + "\n    |");
            }
            if (event.type == sf::Event::KeyPressed){
                // Escape pressed: exit
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::P) {
                    playMusic = true;
                }
                // stop the music and go back to main menu
                if (event.key.code == sf::Keyboard::Enter) {
                    music.stop();
                    playMusic = false;
                }
                // Pause the song
                if (event.key.code == sf::Keyboard::Down) {
                    music.pause();
                }
                // Play the song if paused
                if (event.key.code == sf::Keyboard::Up) {
                    music.play();
                }
                //Skip the  next song? Maybe should do with mouse clicks instead
                if (event.key.code == sf::Keyboard::Right)
                {
                    //Stop the current music
                    music.stop();
                    playPrevious = false;
                }
                //Replay the song?
                if (event.key.code == sf::Keyboard::Left) {
                    //stop the music
                    music.stop();
                    //Set the marker to play the previous
                    playPrevious = true;
                }
                //Fast forward
                if (event.key.code == sf::Keyboard::F){
                    songPosition = music.getPlayingOffset() + sf::seconds(7);
                    music.setPlayingOffset(sf::Time(songPosition));
                    timeOfSong.move(10,0);
                }
                //Rewind
                if (event.key.code == sf::Keyboard::R){
                    songPosition = music.getPlayingOffset() - sf::seconds(7);
                    //If we rewind too far then we just restart the song
                    if (songPosition.asSeconds() < 0.0){
                        songPosition = sf::seconds(0);
                    }
                    timeOfSong.move(-10,0);
                    music.setPlayingOffset(sf::Time(songPosition));
                }
                if (event.key.code == sf::Keyboard::M){
                    // change the size of the window
                    window.setSize(sf::Vector2u(300, 75));
                    //Change window size
                    window.setPosition(sf::Vector2i(2580, 1075));
                    changedSize = true;
                }
                if (event.key.code == sf::Keyboard::N){
                    // change the size of the window
                    window.setSize(sf::Vector2u(800, 600));
                    //Change window size
                    window.setPosition(sf::Vector2i(1040, 334));
                    changedSize = false;
                }
            }
        }
        //Plays always no matter if it hits the end or not because of this while loop
        if (playMusic && music.getStatus() == sf::Music::Status::Stopped){
            //musicPlayList.playList(window);
            if (!playPrevious){
                musicPlayList.updateWhichSong();
            }
            musicPlayList.play(songTexture, music, text, font, playPrevious);
            cdShape.setTexture(&songTexture);
            //After getting a new song, reset the text position
            text.setPosition(0, text.getPosition().y);
            window.draw(mainSprite);
            window.draw(loadingCD);
            
           
            //Display the changes
            window.display();
            system("pause");
            sleep(2);
            window.clear();
            music.play();
            /*
            if (song == 1){
                music.setVolume(100);
                //music.setAttenuation(100);
            } else{
                music.setVolume(1);
                //music.setAttenuation(100);
            }
             */
             song += 1;
            //music.setVolume(20);
            //songLength = (int) music.getDuration().asSeconds() % 500;
            songLength = (int) music.getDuration().asSeconds() / 60;
            totalTimeOfSong.setString(totalSongLength + getCurrentTime(music.getDuration().asSeconds()));
            //totalTimeOfSong.setPosition(0, totalTimeOfSong.getPosition().y);
            timeOfSong.setPosition(text.getPosition().x + 150, text.getPosition().y + 520);
            playPrevious = false;
        }
        //Set the position for the time of the song CHANGE THIS!!!
        //timeOfSong.move((float)60/music.getDuration().asSeconds(), 0);
        //timeOfSong.setPosition(timeOfSong.getPosition().x + 20 / music.getDuration().asSeconds(), timeOfSong.getPosition().y);
        // Clear screen
        window.clear();
        if (playMusic && music.getStatus() != sf::Music::Status::Stopped){
            if ((int) music.getDuration().asSeconds() / 60 == (int) songLength){
                //Move text
                text.setPosition(text.getPosition().x + .1, text.getPosition().y);
            }
            if (music.getStatus() != sf::Music::Status::Paused){
                timeOfSong.move((float)60 / (float)(music.getDuration().asSeconds() * frameRate), 0);
            }
            if (timeOfSong.getPosition().x > totalTimeOfSong.getPosition().x + 100){
                timeOfSong.move(totalTimeOfSong.getPosition().x, 0);
            }
            if (text.getPosition().x > window.getSize().x){
                text.setPosition(0, text.getPosition().y);
            }
            timeOfSong.setString(getCurrentTime(music) + "\n    |");
            // Draw the musicAlbumSprite
            window.draw(mainSprite);
            //Displays the current song time for 7 seconds
            if ((displaySongPosition + sf::seconds(7)).asSeconds() > music.getPlayingOffset().asSeconds()){
                window.draw(timeOfSong);
                window.draw(totalTimeOfSong);
            }
            transform.rotate(.15, cdShape.getPosition().x + cdShape.getRadius(), cdShape.getPosition().y + cdShape.getRadius());
            window.draw(cdShape, transform);
            window.draw(innerCutout);
            
            // Draw the string
            window.draw(text);
            
        } else{
            window.draw(displayMenu);
        }
        if (changedSize){
            window.clear();
            if ((int) music.getDuration().asSeconds() / 60 == (int) songLength){
                //Move text
                text.setPosition(text.getPosition().x + .1, text.getPosition().y);
            }
            if (text.getPosition().x > window.getSize().x){
                text.setPosition(0, text.getPosition().y);
            }
            text.setCharacterSize(80);
            window.draw(text);
        } else{
            text.setCharacterSize(30);
        }
        // Update the window
        window.display();
    }
    
}

std::string MusicManager::getCurrentTime(sf::Music &music)
{
    auto strTimeMinutes = std::to_string((int) music.getPlayingOffset().asSeconds() / 60),
     strTimeSeconds = std::to_string(((int) music.getPlayingOffset().asSeconds() % 60));
    //Check if the seconds are only single digits
    if (strTimeSeconds.size() == 1){
        strTimeSeconds = "0" + strTimeSeconds;
    }
    return strTimeMinutes + ":" + strTimeSeconds.at(0) + strTimeSeconds.at(1);
}
std::string MusicManager::getCurrentTime(float songTime){
    std::string strTimeMinutes = std::to_string((int) songTime / 60),
    strTimeSeconds = std::to_string((int) songTime % 60);
    //Check if the seconds are only single digits
    if (strTimeSeconds.size() == 1){
        strTimeSeconds = "0" + strTimeSeconds;
    }
    return strTimeMinutes + ":" + strTimeSeconds.at(0) + strTimeSeconds.at(1);
}
