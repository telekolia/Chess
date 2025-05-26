#include <SFML/Graphics.hpp>
#include <iostream>

#include "Menu/Menu.hpp"
#include "Chessboard/Chessboard.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Шахматы", sf::Style::Default);
    window.setVerticalSyncEnabled(false);

    // Показываем меню
    ShowMenu(window);

    // Если окно не закрыто (нажата кнопка Старт), показываем шахматную доску
    if (window.isOpen()) {
        ShowChessboard(window);
    }

    return 0;
}
