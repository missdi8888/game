#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Map.h"
#include "Wall.h"

Player::Player(Wall * wall) {
    map = new Map();
    currentSprite = -1;
    spriteNum = 0;
    spriteWidth = 84;
    spriteHeight = 97;
    spriteDelay = 0;
    spriteDelayFrames = 80;

    walkDirection = 0;

    x = 200;
    health = 100;
    y = 200;
    vy = 0;
    dx = 0;
    mass = 1.25;
    aY = 0;
    isDragging = false;

    isAlive = true;
    onGround = false;


    this->wall = wall;
    loadTextures();
    loadSound();
    stay();

    healthRect.setFillColor(sf::Color::Green);
    healthRect.setSize(sf::Vector2<float>(health, 25.0));
}


void Player::loadSound() {
    hitSoundBuffer.loadFromFile("../Textures/hitSound.wav");
    hitSound.setBuffer(hitSoundBuffer);
}

void Player::loadTextures() {
    idle.loadFromFile("../Textures/Idle.png");
    attack.loadFromFile("../Textures/Attack.png");
    death.loadFromFile("../Textures/Death.png");
    hurt.loadFromFile("../Textures/Hurt.png");
    walk.loadFromFile("../Textures/Walk.png");
}

void Player::nextSprite(float ms) {
    spriteDelay += ms;
    if (spriteDelay < spriteDelayFrames) {
        return;
    } else {
        spriteDelay = 0;
    }
    switch (currentSprite) {
        case 0:
            if (spriteNum < 2) spriteNum++;
            else spriteNum = 0;
            break;
        case 1:
            if (spriteNum < 3) spriteNum++;
            else {
                currentSprite = -1;
                stay();
            }
            break;
        case 2:
            if (spriteNum < 3) spriteNum++;
            break;
        case 3:
            if (spriteNum < 1) spriteNum++;
            else {
                currentSprite = -1;
                spriteDelayFrames = 80;
                y -= 12;
                stay();
            }
            break;
        case 4:
            if (spriteNum < 5) spriteNum++;
            else spriteNum = 0;
            break;
    }
}

void Player::handleGravity(float ms) {
    if (!ms) return;
    vy += (g + aY) / (ms * mass);
    float tempY = y + vy;
    sf::Rect<float> rect = sf::Rect<float>(x, tempY + spriteHeight - 1, spriteWidth - 1, 1);
    sf::Rect<float> rect2 = sf::Rect<float>(x, tempY, spriteWidth - 1, 1);
    onGround = map->isNextCollide(rect) || wall->isNextCollide(rect);
    if (onGround || map->isNextCollide(rect2) || wall->isNextCollide(rect2)) {
        aY = 0;
        vy = 0;
    } else {
        y = tempY;
        aY--;
        if (aY < 0) aY = 0;
    }
}

sf::Rect<float> Player::getPosition() { return sprite.getGlobalBounds(); }

void Player::blowUp() {
    health -= 50;
    if (!isAlive) return;
    if (currentSprite != 3) {
        currentSprite = 3;
        spriteDelayFrames = 250;
        sprite.setTexture(hurt);
        spriteWidth = 81;
        spriteHeight = 85;
        spriteNum = 0;
    }
}

void Player::heal() {
    health += 50;
    if (health > 100) {
        health = 100;
    }
}

void Player::stay() {
    if (!isAlive || currentSprite == 1 || currentSprite == 3) return;
    if (currentSprite != 0) {
        currentSprite = 0;
        sprite.setTexture(idle);
        spriteWidth = 84;
        spriteHeight = 97;
        spriteNum = 0;
    }
}

void Player::die() {
    isAlive = false;
    if (currentSprite != 2) {
        spriteDelayFrames = 800;
        currentSprite = 2;
        sprite.setTexture(death);
        spriteWidth = 94;
        spriteHeight = 75;
        spriteNum = 0;
    }
}

void Player::hit() {
    if (!isAlive) return;
    if (currentSprite != 1) {
        sf::Rect<float> r = getPosition();
        if (!walkDirection) {
            r = sf::Rect<float>(r.left, r.top  + r.height / 2, r.width + 20, 1);
        } else {
            r = sf::Rect<float>(r.left - 20, r.top + r.height / 2, r.width, 1);
        }
        wall->hit(r);
        currentSprite = 1;
        hitSound.play();
        sprite.setTexture(attack);
        spriteWidth = 103;
        spriteHeight = 97;
        spriteNum = 0;
    }
}

void Player::walkRight() {
    if (!isAlive || currentSprite == 3 || currentSprite == 1) return;
    dx += 5;
    walkDirection = 0;
    if (currentSprite != 4) {
        currentSprite = 4;
        sprite.setTexture(walk);
        spriteWidth = 83;
        spriteHeight = 95;
        spriteNum = 0;
    }
}

void Player::walkLeft() {
    if (!isAlive || currentSprite == 3 || currentSprite == 1) return;
    dx -= 5;
    walkDirection = 1;
    if (currentSprite != 4) {
        currentSprite = 4;
        sprite.setTexture(walk);
        spriteWidth = 83;
        spriteHeight = 95;
        spriteNum = 0;
    }
}

void Player::jump() {
    if (onGround && isAlive && currentSprite != 1 && currentSprite != 3) {
        aY = -250;
        onGround = false;
    }
}

void Player::drag(float dx, float dy) {
    sf::Rect<float> rect = sf::Rect<float>(dx, dy, spriteWidth, spriteHeight);
    if (isDragging
        && isAlive
        && !map->isNextCollide(sf::Rect<float>(dx, dy, spriteWidth, spriteHeight))
        && !wall->isNextCollide(rect)
        && dx > 0
        && dx < 1280
        && dy > 0
        && dy < 800
            ) {
        x = dx;
        y = dy;
        sprite.setPosition(x, y);
    }
}
void Player::setIsDrag(bool flag) { isDragging = flag; } //установка переменной
bool Player::isDrag() { return isDragging; } //получение переменной

void Player::update(float ms) {
    nextSprite(ms);
    if (!walkDirection) {
        sprite.setTextureRect(sf::Rect<int>(spriteNum * spriteWidth, 0, spriteWidth, spriteHeight));
    } else {
        sprite.setTextureRect(sf::Rect<int>(spriteWidth + spriteNum * spriteWidth, 0, -spriteWidth, spriteHeight));
    }
    if (isDragging) return;

    handleGravity(ms);

    if (isAlive) {

        sf::Rect<float> rect = sf::Rect<float>(x + dx, y, spriteWidth, spriteHeight);
        if (!map->isNextCollide(rect) && !wall->isNextCollide(rect)) {
            x += dx;
            if (dx < -5) {
                dx += 5;
            } else if (dx > 5) {
                dx -= 5;
            } else {
                dx = 0;
            }
        } else {
            dx = 0;
        }

        //health -= 0.5;
        if (health < 0.1) {
            die();
        }
    }
    sprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow &window) {
    sf::Rect<float> playerPosition = getPosition();
    healthRect.setPosition(playerPosition.left + (playerPosition.width - health) / 2, playerPosition.top - 35);
    healthRect.setSize(sf::Vector2<float>(health, 25.0));
    window.draw(healthRect);
    window.draw(sprite);
}