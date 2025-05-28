#include <SFML/Graphics.hpp>
#include <iostream>

#include "Menu/Menu.hpp"
#include "Menu/TimeMenu.hpp"
#include "Chessboard/Chessboard.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Шахматы");

    while (window.isOpen()) {
        showMenu(window);  // Главное меню

        if (!window.isOpen())
            break;

        int selectedTime = showTimeMenu(window);  // Выбор времени (или его пропуск)

        if (!window.isOpen())
            break;

        if (selectedTime == -1)
            continue;

        ShowChessboard(window, selectedTime);
    }

    return 0;
}
