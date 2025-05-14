#include <SFML/Graphics.hpp>
#include <iostream>

#include "Menu/Menu.hpp"

// Функция для отображения шахматной доски (заглушка)
void showChessBoard(sf::RenderWindow& window) {
    // Здесь будет код для отображения шахматной доски
    sf::Font font;
    font.loadFromFile("../font/Tiny5-Regular.ttf");

    sf::Text text("Chess board", font, 30);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(250, 300);

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

        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Шахматы");

    // Показываем меню
    showMenu(window);

    // Если окно не закрыто (нажата кнопка Старт), показываем шахматную доску
    if (window.isOpen()) {
        showChessBoard(window);
    }

    return 0;
}
