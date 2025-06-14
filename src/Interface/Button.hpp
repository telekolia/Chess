#include <SFML/Graphics.hpp>
#include <iostream>

class Button : public sf::Drawable {
 private:
    sf::Text m_text;
    sf::FloatRect m_bounds;
    sf::Color m_hoverColor;
    sf::Color m_normalColor;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 public:
    Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& color,
           const sf::Color& hoverColor);

    bool isMouseOver(const sf::RenderWindow& window) const;
    void update(const sf::RenderWindow& window);

    sf::Text& getText();
};
