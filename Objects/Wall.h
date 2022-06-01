#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall {
private:
    sf::Texture wallT;
    sf::Sprite wall;

    float health;
    sf::RectangleShape healthRect;

    void loadTexture();

public:
    Wall();

    void hit(sf::Rect<float> playerRect);

    bool isNextCollide(sf::Rect<float> &rect);

    void draw(sf::RenderWindow &window);
};

#endif