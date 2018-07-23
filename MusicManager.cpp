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
    SongList musicPlayList;
    musicPlayList.buildList(resourcePath() + "musicPlayList.csv");
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML\nHelloWorld", font, 50);
    text.setFillColor(sf::Color::Black);
    
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    sf::Transform transform;
    //sf::Sprite sprite;
    sprite.setColor(sf::Color::Blue);
    Disc cdShape(200, 35, *(new sf::Vector2f(window.getSize().x/4, window.getSize().y/5)), &texture);
    Disc innerCutout(50, 35, *(new sf::Vector2f(cdShape.getPosition().x + cdShape.getRadius() - 50, cdShape.getPosition().y + cdShape.getRadius() - 50)), *(new sf::Color(sf::Color::Black)));
    
    // Play the music
    //music.play();
    bool playMusic = false;
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
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                playMusic = true;
            }
        }
        
        // Clear screen
        window.clear();
        
        // Draw the sprite
        window.draw(sprite);
        
        transform.rotate(.25, cdShape.getPosition().x + cdShape.getRadius(), cdShape.getPosition().y + cdShape.getRadius());
        window.draw(cdShape, transform);
        window.draw(innerCutout);
        // Draw the string
        window.draw(text);
        //Plays always no matter if it hits the end or not because of this while loop
        if (playMusic){
            musicPlayList.playList(window);
            playMusic = false;
        }
        // Update the window
        window.display();
    }
    
}
