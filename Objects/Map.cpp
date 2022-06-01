#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Map.h"

Map::Map() {
    map = std::vector<std::string>({
           "0000000000000000000000000000000000000000",
           "7                                       ",
           "7                                       ",
           "7                                       ",
           "7                                       ",
           "03331                                   ",
           "00000    2331                           ",
           "7        00001               23333333330",
           "7                            00000000000",
           "7                                      6",
           "7                                      6",
           "7                  2331                6",
           "7                  0000                6",
           "7                                      6",
           "7                                      6",
           "7                          2331        6",
           "031                       20000        6",
           "000                233333300000        6",
           "7                  000000000000        6",
           "7         2331                         6",
           "03331     0000                         6",
           "00000                                  6",
           "7                                      6",
           "7                                      6",
           "0333333333333333333333333333333333333330",
   });

    loadMapTiles();
    loadBg();
    sprite.setTexture(tiles);
}


    void Map::loadMapTiles() {
        tiles.loadFromFile("../Textures/Tiles.png");
        sprite.setScale(1.0 / 16, 1.0 / 16);
    }

    void Map::loadBg() {
        bg.loadFromFile("../Textures/GameBG.png");
        bgSprite.setTexture(bg);
        bgSprite.setScale(0.75, 0.75);
    }

    bool Map::isNextCollide(sf::Rect<float> rect) {
        bool flag = false;
        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                if (map[i][j] == ' ') {
                    continue;
                }

                sf::Rect<float> tileRect((float) SideLength * j, (float) SideLength * i, (float) SideLength,
                                         (float) SideLength);


                if (rect.intersects(tileRect)) {
                    flag = true;
                }
            }
        }
        return flag;
    }

    void Map::draw(sf::RenderWindow &window) {
        window.draw(bgSprite);
        for (int i = 0; i < Height; i++)
            for (int j = 0; j < Width; j++)
            {
                if (map[i][j] == ' ') {
                    continue;
                } else {
                    int textureNum = map[i][j] - '0';
                    sprite.setTextureRect(sf::Rect<int>(512 * textureNum, 0, 512, 512));
                    sprite.setPosition((float) SideLength * j, (float) SideLength * i);
                    window.draw(sprite);
                }
            }
    }