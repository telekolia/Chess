#include "Board.hpp"
#include <SFML/Graphics.hpp>

Board::Board() {
    load();
}

// Загрузка ресурсов доски и установка параметров при её инициализации
void Board::load(){
    m_texture.loadFromFile("../res/chess_green/board.png"); // путь всегда пишем из build
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition({-16.f, -16.f});
    m_sprite.scale(4.f, 4.f);

    float x = 0;
    float y = 0;

    for (int i = 0; i < 64; ++i) {
        x = 88.f * (i % 8) - 8.f;
        y = 88.f * (i / 8) - 8.f;
        squares[i].height = 88;
        squares[i].width = 88;
        squares[i].left = x;
        squares[i].top = y;
    }
}

bool Board::isMouseOver(const sf::RenderWindow& window, sf::FloatRect square) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return square.contains(mousePos);
}

// Рендер доски
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

int Board::getMousePosition(const sf::RenderWindow& window) const {
    for(int i = 0; i < 64; ++i) {
        if (isMouseOver(window, squares[i])) {
            return i;
        }
    }

    return -1;
}
