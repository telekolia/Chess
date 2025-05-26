#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Board {
 private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

 public:
    Board();
    void load();
    void draw(sf::RenderWindow& window) const;
};
