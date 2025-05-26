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
}

// Рендер доски
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
