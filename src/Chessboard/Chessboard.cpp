#include <SFML/Graphics.hpp>
#include <iostream>
#include "ChessEngine/ChessEngine.hpp"

// функция работы сцены игры
void ShowChessboard(sf::RenderWindow& window) {
    ChessEngine chess;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if((event.mouseButton.x >= 0) && (event.mouseButton.x <= 720) && (0 <= event.mouseButton.y) && (event.mouseButton.y <= 720)){
                        unsigned int buttonPos{(event.mouseButton.x/90) + ((event.mouseButton.y/90) * (8 * (720/window.getSize().y)))};

                        if(!chess.getSelected())
                            chess.selectPiece(buttonPos);
                        else
                            chess.moveSelected(buttonPos);
                    }
                    else if((720 <= event.mouseButton.x) && (event.mouseButton.x <= 900) && (5 <= event.mouseButton.y) && (event.mouseButton.y <= 45)){
                        chess.restart();
                    }
                }
            }
        }

        window.clear(sf::Color(0, 55, 22));
        window.draw(chess);
        window.display();
    }
}
