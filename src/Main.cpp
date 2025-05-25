#include <SFML/Graphics.hpp>
#include <iostream>

#include "Menu/Menu.hpp"
#include "Menu/TimeMenu.hpp"

void showChessBoard(sf::RenderWindow& window, int minutesPerPlayer) {
    sf::Font font;
    if (!font.loadFromFile("../font/Tiny5-Regular.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        return;
    }

    std::string label = (minutesPerPlayer > 0)
        ? "Chess board - " + std::to_string(minutesPerPlayer) + " min"
        : "Chess board without timer";

    sf::Text text(label, font, 30);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(300, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
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

    while (window.isOpen()) {
        showMenu(window);  // Главное меню

        if (!window.isOpen()) break;

        int selectedTime = showTimeMenu(window);  // Выбор времени (или его пропуск)

        if (!window.isOpen()) break;

        // Пользователь вернулся на главное меню — перезапускаем цикл
        if (selectedTime == -1) continue;

        // Иначе переходим на доску
        showChessBoard(window, selectedTime);
    }

    return 0;
}
