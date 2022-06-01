#include <SFML/Graphics.hpp>
#include "Heart.h"

Heart::Heart(float x, float y) {
    this->x = x;
    this->y = y;
    isAlive = true;

    loadTexture();
    sprite.setPosition(x, y);
    sprite.setScale(0.5, 0.5);
}

void Heart::loadTexture() {
    t.loadFromFile("../Textures/heart.png");
    sprite.setTexture(t);
}

void Heart::heal() {
    isAlive = false;
}

bool Heart::getIsAlive() { return isAlive; }

sf::Rect<float> Heart::getPosition() { return sprite.getGlobalBounds(); }

void Heart::draw(sf::RenderWindow &window) {
    if (isAlive) {
        window.draw(sprite);
    }
}