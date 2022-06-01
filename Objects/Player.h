#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.h"
#include "Wall.h"

class Player {
private:
    float const g = 9.81;

    Map *map;
    Wall *wall;
    sf::Sprite sprite;

    sf::RectangleShape healthRect;
    float health;

    sf::SoundBuffer hitSoundBuffer;
    sf::Sound hitSound;
    sf::Texture idle; // 0
    sf::Texture attack; // 1
    sf::Texture death; // 2
    sf::Texture hurt; // 3
    sf::Texture walk; // 4
    int currentSprite;
    int spriteNum;
    int spriteWidth;
    int spriteHeight;
    float spriteDelay;
    float spriteDelayFrames;

    int walkDirection;

    float x;
    float y;
    float vy;
    float dx;
    float mass;
    float aY;
    bool isDragging;

    bool isAlive;
    bool onGround;

    void loadSound();

    void loadTextures();

    void nextSprite(float ms);

    void handleGravity(float ms);

public:

    sf::Rect<float> getPosition();

    void blowUp();

    void heal();

    void stay();

    void die();

    void hit();

    void walkRight();

    void walkLeft();

    void jump();

    Player(Wall * wall);

    void drag(float dx, float dy);
    void setIsDrag(bool flag);
    bool isDrag();

    void update(float ms);
    void draw(sf::RenderWindow &window);
};

#endif