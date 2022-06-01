#ifndef HEART_H
#define HEART_H

#include <SFML/Graphics.hpp>

class Heart {
private:
    float x, y;
    sf::Texture t;
    sf::Sprite sprite;
    bool isAlive;
    void loadTexture();

public:
    Heart(float x, float y);
    void heal();
    bool getIsAlive();
    sf::Rect<float> getPosition();
    void draw(sf::RenderWindow &window);
};

#endif