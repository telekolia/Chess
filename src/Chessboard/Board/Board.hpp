#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Board : public sf::Drawable {
 private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 public:
    Board();
    void load();
};
