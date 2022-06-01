#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Objects/Player.h"
#include "Objects/Bomb.h"
#include "Objects/Heart.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML window");
    window.setFramerateLimit(60);

    std::vector<Bomb *> bombs = std::vector<Bomb *>({
        new Bomb(100, 82),
        new Bomb(1000, 145),
        new Bomb(1180, 690),
    });

    std::vector<Heart *> hearts = std::vector<Heart *>({
        new Heart(40, 450),
        new Heart(700, 475),
    });

    Map map;
    Wall wall;
    Player player(&wall);

    float dX = 0;
    float dY = 0;

    sf::Clock clock;
    sf::Time frameTime{ sf::Time::Zero };

    sf::RectangleShape winRectangle;
    winRectangle.setPosition(1248, 32);
    winRectangle.setSize(sf::Vector2<float>(32, 192));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

        window.clear(sf::Color(255, 255, 255, 255));

        if (event.type == sf::Event::MouseButtonPressed)
            if (event.key.code == sf::Mouse::Left)
                if (player.getPosition().contains(pos.x, pos.y)) {
                    player.setIsDrag(true);
                    dX = pos.x - player.getPosition().left;
                    dY = pos.y - player.getPosition().top;
                }

        if (event.type == sf::Event::MouseButtonReleased)
            if (event.key.code == sf::Mouse::Left)
                player.setIsDrag(false);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.jump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) player.hit();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.walkRight();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.walkLeft();
        else player.stay();

        map.draw(window);
        wall.draw(window);

        player.update(frameTime.asMilliseconds());
        player.drag(pos.x - dX, pos.y - dY);

        if (winRectangle.getGlobalBounds().intersects(player.getPosition())) {
            return EXIT_SUCCESS;
        }

        player.draw(window);

        for (Bomb* bomb : bombs) {
            if (!player.isDrag() && bomb->getIsAlive() && player.getPosition().intersects(bomb->getPosition())) {
                player.blowUp();
                bomb->blowUp();
            }
            bomb->draw(window);
        }

        for (Heart* heart : hearts) {
            if (!player.isDrag() && heart->getIsAlive() && player.getPosition().intersects(heart->getPosition())) {
                player.heal();
                heart->heal();
            }
            heart->draw(window);
        }

        frameTime = clock.restart();
        window.display();
    }

    return EXIT_SUCCESS;
}