//
//  Disc.hpp
//  Music Manager
//
//  Created by Paul Valdez on 7/22/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//

#ifndef Disc_hpp
#define Disc_hpp

#include <SFML/Graphics.hpp>

//#define RADIUS 50

class Disc : public sf::CircleShape
{
public:
    //Constructor 1 ~ Texture has to be a pointer because the circle shape can only access it while it exists
    Disc(double radius, int numPoints, sf::Vector2f &position, sf::Texture * texture) : sf::CircleShape(radius, numPoints)
    {
        this -> setTexture(texture);
        this -> setPosition(position);
    }
    //Constructor for a disc without graphics
    Disc(double radius, int numPoints, sf::Vector2f &position, sf::Color &color) : sf::CircleShape(radius, numPoints)
    {
        this -> setFillColor(color);
        this -> setPosition(position);
    }
    // Disc(double radius, int numPoints, sf::Vector2f &position) : sf::CircleShape
};

#endif /* Disc_hpp */
