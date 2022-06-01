#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define Height 25
#define Width 40
#define SideLength 32

class Map {
private:
    sf::Texture tiles;
    sf::Sprite sprite;
    sf::RectangleShape square;
    sf::Texture bg;
    sf::Sprite bgSprite;

    std::vector<std::string> map;

    void loadMapTiles();

    void loadBg();

public:
    Map();

    bool isNextCollide(sf::Rect<float> rect);

    void draw(sf::RenderWindow &window);
};

#endif