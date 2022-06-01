#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>

class Bomb {
private:
    float x, y;
    sf::Texture t;
    sf::Sprite sprite;
    bool isAlive;
    void loadTexture();
public:
    Bomb(float x, float y);
    void blowUp();
    bool getIsAlive();
    sf::Rect<float> getPosition();
    void draw(sf::RenderWindow &window);
};

#endif