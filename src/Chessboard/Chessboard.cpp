#include <SFML/Graphics.hpp>
#include <iostream>
#include "ChessEngine/ChessEngine.hpp"
#include "../Interface/Button.hpp"

// функция работы сцены игры
void ShowChessboard(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../font/Tiny5-Regular.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        return;
    }

    Button restartButton("Restart", font, 48, sf::Vector2f(820, 600), sf::Color::Magenta, sf::Color::Yellow);
    Button exitButton("Exit", font, 48, sf::Vector2f(850, 650), sf::Color::Magenta, sf::Color::Yellow);

    ChessEngine chess;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if((event.mouseButton.x >= 0) && (event.mouseButton.x <= 720) && (event.mouseButton.y >= 0) && (event.mouseButton.y <= 720)){
                        unsigned int buttonPos{(event.mouseButton.x/90) + ((event.mouseButton.y/90) * (8 * (720/window.getSize().y)))};

                        if(!chess.getSelected())
                            chess.selectPiece(buttonPos);
                        else
                            chess.moveSelected(buttonPos);
                    }
                    if(restartButton.isMouseOver(window)){
                        chess.restart();
                    }
                    if(exitButton.isMouseOver(window)) {
                        window.close();
                    }
                }
            }

            restartButton.update(window);
            exitButton.update(window);
        }

        window.clear(sf::Color(0, 55, 22));
        window.draw(chess);
        window.draw(restartButton);
        window.draw(exitButton);
        window.display();
    }
}
