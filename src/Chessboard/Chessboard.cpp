#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
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

    sf::Clock clock;
    int duration1 = gameLatensy*60;
    int duration2 = gameLatensy*60;
    sf::String timerString1, timerString2;

    sf::Font timerFont1;
    sf::Text timerText1;
    timerFont1.loadFromFile("../font/Tiny5-Regular.ttf");
    timerText1.setFont(timerFont1);
    timerText1.setString("00:00");
    timerText1.setCharacterSize(20);
    timerText1.setFillColor(sf::Color::White);
    timerText1.setPosition(850, 10);

    sf::Font timerFont2;
    sf::Text timerText2;
    timerFont2.loadFromFile("../font/Tiny5-Regular.ttf");
    timerText2.setFont(timerFont2);
    timerText2.setString("00:00");
    timerText2.setCharacterSize(20);
    timerText2.setFillColor(sf::Color::Black);
    timerText2.setPosition(850, 40);

    float fMinutes1, fMinutes2, fSeconds1, fSeconds2;
    int intMinutes1, intMinutes2, intSeconds1, intSeconds2;
    sf::String stringMinutes1, stringMinutes2;
    sf::String stringSeconds1, stringSeconds2;

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

        sf::Time time = clock.restart();

        if (chess.getSelected()){
            if (chess.getPlayerturn()){
                if (duration1 > 0){
                    duration1 -= time.asSeconds();

                    fMinutes1 = duration1/60;
                    fSeconds1 = duration1%60;

                    intSeconds1 = static_cast<int>(fSeconds1);
                    intMinutes1 = static_cast<int>(fMinutes1);

                    stringSeconds1=std::to_string(intSeconds1);
                    stringMinutes1=std::to_string(intMinutes1);

                    if (intMinutes1<=0){
                        stringMinutes1="00";
                    }

                    if (intSeconds1<=0){
                        stringSeconds1="00";
                    }
                    else if (intSeconds1<10){
                        stringSeconds1 = "0"+stringSeconds1;
                    }

                    timerString1 = stringMinutes1+":"+stringSeconds1;

                    timerText1.setString(timerString1);
                }
            }
            else{
                if (duration2 > 0){
                    duration2 -= time.asSeconds();

                    fMinutes2 = duration2/60;
                    fSeconds2 = duration2%60;

                    intSeconds2 = static_cast<int>(fSeconds2);
                    intMinutes2 = static_cast<int>(fMinutes2);

                    stringSeconds2=std::to_string(intSeconds2);
                    stringMinutes2=std::to_string(intMinutes2);

                    if (intMinutes2<=0){
                        stringMinutes2="00";
                    }

                    if (intSeconds2<=0){
                        stringSeconds2="00";
                    }
                    else if (intSeconds2<10){
                        stringSeconds2 = "0"+stringSeconds2;
                    }

                    timerString2 = stringMinutes2+":"+stringSeconds2;

                    timerText2.setString(timerString2);
                }
            }
        }

        window.clear(sf::Color(0, 55, 22));
        window.draw(board);
        window.draw(chess);
        window.draw(restartButton);
        window.draw(exitButton);
        window.draw(timerText1);
        window.draw(timerText2);
        window.display();
    }
}
