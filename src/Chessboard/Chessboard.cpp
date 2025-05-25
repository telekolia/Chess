#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void drawCircleShape(sf::RenderWindow& window, sf::Vector2f poz) {
    sf::CircleShape circle(30, 30);
    circle.setPosition(poz);
    window.draw(circle);
}

// Функция для отображения шахматной доски (заглушка)
void showChessBoard(sf::RenderWindow& window) {
    int x=147, y=122;
    sf::Texture pawn, click_pawn;
    pawn.loadFromFile("../res/chess_green/black_pawn.png");
    click_pawn.loadFromFile("../res/chess/black_pawn.png");

    sf::Sprite sprite(pawn);
    sprite.setTexture(pawn);

    sprite.setPosition(147,122);

    std::vector<sf::Vector2f> v;

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

            switch (event.key.code){
                    case sf::Keyboard::W: {
                        sprite.setTexture(click_pawn);
                        for (int i = 147; i<609; i+=66){
                            for (int j = 112; j<584 ; j+=66){
                                if (i== x+66 || i==x-66 || j==y+66 || j==y-66){
                                    v.push_back({i, j});
                                }
                            }
                        }
                        break;
                    }
            }
        }

        window.clear(sf::Color(0, 55, 22));
        window.draw(board);
        window.draw(sprite);
        for (sf::Vector2f i : v) {
            drawCircleShape(window, i);
        }
        window.display();
    }
}

// //создаем фигуру
// void showFigure(sf::RenderWindow& window, int x, int y){
//     sf::Texture pawn, click_pawn;
//     pawn.loadFromFile("../res/chess_green/black_pawn.png");
//     click_pawn.loadFromFile("../res/chess/black_pawn.png");

//     sf::Sprite sprite;
//     sprite.setTexture(pawn);

//     sprite.setPosition(147,122);

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::KeyPressed){
//                 switch (event.key.code){
//                     case sf::Keyboard::W: {
//                         sprite.setTexture(click_pawn);
//                         for (int i = 147; i<609; i+=66){
//                             for (int j = 112; j<584 ; j+=66){
//                                 if (i== x+66 || i==x-66 || j==y+66 || j==y-66){
//                                     sf::CircleShape circle(30, 30);
//                                     circle.setPosition(i, j);
//                                     window.draw(circle);
//                                 }
//                             }
//                         }
//                         break;
//                     }
//                 }
//             }
//         }
//         window.draw(sprite);

//     }
// }
