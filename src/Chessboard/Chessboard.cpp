#include <SFML/Graphics.hpp>
#include <iostream>
#include "ChessEngine/ChessEngine.hpp"
#include "../Interface/Button.hpp"
#include "Board/Board.hpp"

// функция работы сцены игры
void ShowChessboard(sf::RenderWindow& window, int gameLatensy) {
    sf::Font font;
    if (!font.loadFromFile("../font/Tiny5-Regular.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        return;
    }

    Button restartButton("Restart", font, 48, sf::Vector2f(820, 600), sf::Color::Magenta, sf::Color::Yellow);
    Button exitButton("Exit", font, 48, sf::Vector2f(850, 650), sf::Color::Magenta, sf::Color::Yellow);

    Board board;

    ChessEngine chess;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if((event.mouseButton.x >= 0) && (event.mouseButton.x <= 720) && (event.mouseButton.y >= 0) && (event.mouseButton.y <= 720)){
                        int squareNumber = board.getMousePosition(window);

                        if(!chess.getSelected())
                            chess.selectPiece(squareNumber);
                        else
                            chess.moveSelected(squareNumber);
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
        window.draw(board);
        window.draw(chess);
        window.draw(restartButton);
        window.draw(exitButton);
        window.display();
    }
}
