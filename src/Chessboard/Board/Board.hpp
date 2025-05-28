#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Board : public sf::Drawable {
 private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    sf::FloatRect squares[64];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isMouseOver(const sf::RenderWindow& window, sf::FloatRect square) const;
 public:
    Board();
    void load();

    int getMousePosition(const sf::RenderWindow& window) const;
};
