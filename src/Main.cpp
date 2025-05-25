#include <SFML/Graphics.hpp>
#include <iostream>

#include "Menu/Menu.hpp"
#include "Chessboard/Chessboard.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Шахматы", sf::Style::Default);

    // Показываем меню
    showMenu(window);

    // Если окно не закрыто (нажата кнопка Старт), показываем шахматную доску
    if (window.isOpen()) {
        showChessBoard(window);
    }

    return 0;
}
