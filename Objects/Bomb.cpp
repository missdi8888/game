#include "Bomb.h"

Bomb::Bomb(float x, float y) {
    isAlive = true;

    this->x = x;
    this->y = y;
    loadTexture();
    sprite.setPosition(x, y);
    sprite.setScale(0.5, 0.5);
}

void Bomb::blowUp() {
    isAlive = false;
}

void Bomb::loadTexture() {
    t.loadFromFile("../Textures/bomb.png");
    sprite.setTexture(t);
}

bool Bomb::getIsAlive() { return isAlive; }

sf::Rect<float> Bomb::getPosition() {
    return sprite.getGlobalBounds();
}

void Bomb::draw(sf::RenderWindow &window) {
    if (isAlive) {
        window.draw(sprite);
    }
}