#include <SFML/Graphics.hpp>
#include <iostream>

const int defaultChessSet [8][8] = {{12, 13, 14, 15, 16, 14, 13, 12},
                                    {11, 11, 11, 11, 11, 11, 11, 11},
                                    {00, 00, 00, 00, 00, 00, 00, 00},
                                    {00, 00, 00, 00, 00, 00, 00, 00},
                                    {01, 01, 01, 01, 01, 01, 01, 01},
                                    {02, 03, 04, 05, 06, 04, 03, 02}};

// Функция для отображения шахматной доски (заглушка)
void showChessBoard(sf::RenderWindow& window) {
    // Здесь будет код для отображения шахматной доски
    sf::Font font;
    font.loadFromFile("../font/Tiny5-Regular.ttf");

    sf::Texture boardTexture;
    boardTexture.loadFromFile("../res/chess_green/board_alt.png"); // путь всегда пишем из build
    sf::Sprite board(boardTexture);
    board.setPosition({0.f, -25.f});
    board.scale(3.f, 3.f);

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
        window.draw(board);
        window.display();
    }
}
