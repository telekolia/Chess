#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "../Interface/Button.hpp"

class TimeOption {
 private:
    int timeValue;
    Button button;
    bool selected = false;
    sf::FloatRect circleBounds;

 public:
    TimeOption(int value, const sf::Font& font, const sf::Vector2f& pos)
        : timeValue(value), button(std::to_string(value) + " min", font, 30, pos, sf::Color::White, sf::Color::Yellow) {
        float circleX = pos.x - 30;
        float circleY = pos.y + 8;
        circleBounds = sf::FloatRect(circleX, circleY, 20, 20);
    }

    int getTime() const { return timeValue; }

    void draw(sf::RenderWindow& window) {
        window.draw(button);

        float circleX = button.getText().getPosition().x - 30;
        float circleY = button.getText().getPosition().y + 8;

        sf::CircleShape outline(10);
        outline.setPosition(circleX, circleY);
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineColor(sf::Color::White);
        outline.setOutlineThickness(2);
        window.draw(outline);

        if (selected) {
            sf::CircleShape fill(6);
            fill.setFillColor(sf::Color::Yellow);
            fill.setPosition(circleX + 4, circleY + 4);
            window.draw(fill);
        }

        circleBounds = sf::FloatRect(circleX, circleY, 20, 20);
    }

    void update(sf::RenderWindow& window) { button.update(window); }

    bool isClicked(sf::RenderWindow& window) const {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return button.isMouseOver(window) || circleBounds.contains(mousePos);
    }

    void setSelected(bool sel) { selected = sel; }

    bool isSelected() const { return selected; }

    sf::Text& getText() { return button.getText(); }
};

// Экран выбора времени (0 = без таймера, > 0 = минуты, -1 = вернуться)
int showTimeMenu(sf::RenderWindow& window);
