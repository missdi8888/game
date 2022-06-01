#include <SFML/Graphics.hpp>
#include "Wall.h"

Wall::Wall() {
    health = 100;
    loadTexture();
    healthRect.setFillColor(sf::Color::Red);
}

void Wall::loadTexture() {
    wallT.loadFromFile("../Textures/wall.png");
    wall.setTexture(wallT);
    wall.setScale(0.33, 0.33);
    wall.setPosition(1150, 124);
}

void Wall::hit(sf::Rect<float> playerRect) {
    if (health > 0 && wall.getGlobalBounds().intersects(playerRect)) {
        health -= 20;
    }
}

bool Wall::isNextCollide(sf::Rect<float> &rect) {
    return health > 0 && rect.intersects(wall.getGlobalBounds());
}

void Wall::draw(sf::RenderWindow &window) {
    if (health > 0) {
        sf::Rect<float> wallPosition = wall.getGlobalBounds();
        healthRect.setPosition(wallPosition.left + (wallPosition.width - health) / 2, wallPosition.top - 25);
        healthRect.setSize(sf::Vector2<float>(health, 12.0));
        window.draw(healthRect);
        window.draw(wall);
    }
}