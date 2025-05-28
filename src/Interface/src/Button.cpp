#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Button.hpp"

Button::Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& color,
               const sf::Color& hoverColor)
    : m_hoverColor(hoverColor), m_normalColor(color) {
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(color);
    m_text.setPosition(position);
    // Устанавливаем границы кнопки (для проверки наведения)
    m_bounds = m_text.getGlobalBounds();
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(m_text);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return m_bounds.contains(mousePos);
}

void Button::update(const sf::RenderWindow& window) {
    if (isMouseOver(window)) {
        m_text.setFillColor(m_hoverColor);
    } else {
        m_text.setFillColor(m_normalColor);
    }
}

sf::Text& Button::getText() {
    return m_text;
}
