#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board/Board.hpp"

const char defaultChessSet [8][8] = {{'R', 'H', 'B', 'K', 'Q', 'B', 'H', 'R'},
                                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                                    {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
                                    {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
                                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                                    {'R', 'H', 'B', 'K', 'Q', 'B', 'H', 'R'}};

// функция работы сцены игры
void ShowChessboard(sf::RenderWindow& window) {
    Board board;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear(sf::Color(0, 55, 22));
        board.draw(window);
        window.display();
    }
}
