#include "Board.hpp"
#include <SFML/Graphics.hpp>

Board::Board() {
    load();
}

// Загрузка ресурсов доски и установка параметров при её инициализации
void Board::load(){
    m_texture.loadFromFile("../res/chess_green/board.png"); // путь всегда пишем из build
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition({0.f, 0.f});
    m_sprite.scale(4.f, 4.f);
}

// Рендер доски
void Board::draw(sf::RenderWindow& window) const{
    window.draw(m_sprite);
}
