#include "TimeMenu.hpp"

class TimerOption {
 private:
    Button button;
    sf::FloatRect circleBounds;
    bool selected = false;

 public:
    TimerOption(const sf::Font& font, const sf::Vector2f& pos) : button("Timer", font, 30, pos, sf::Color::White, sf::Color::Yellow) {
        float circleX = pos.x - 30;
        float circleY = pos.y + 8;
        circleBounds = sf::FloatRect(circleX, circleY, 20, 20);
    }

    void draw(sf::RenderWindow& window) {
        button.draw(window);

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

int showTimeMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../font/Tiny5-Regular.ttf")) {
        return 0;
    }

    sf::Text title("Game Settings", font, 50);
    title.setFillColor(sf::Color::Yellow);
    sf::FloatRect titleBounds = title.getGlobalBounds();
    title.setPosition((1080 - titleBounds.width) / 2.f, 50);

    TimerOption timerOption(font, sf::Vector2f(100, 150));
    bool timerEnabled = false;
    int selectedTime = 0;

    std::vector<std::shared_ptr<TimeOption>> timeButtons = {
        std::make_shared<TimeOption>(60, font, sf::Vector2f(300, 230)),
        std::make_shared<TimeOption>(30, font, sf::Vector2f(300, 280)),
        std::make_shared<TimeOption>(15, font, sf::Vector2f(300, 330)),
        std::make_shared<TimeOption>(5, font, sf::Vector2f(500, 230)),
        std::make_shared<TimeOption>(3, font, sf::Vector2f(500, 280)),
        std::make_shared<TimeOption>(1, font, sf::Vector2f(500, 330)),
    };

    Button returnButton("Return", font, 28, sf::Vector2f(30, 660), sf::Color::White, sf::Color::Red);
    Button startButton("Start", font, 28, sf::Vector2f(920, 660), sf::Color::White, sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (timerOption.isClicked(window)) {
                    timerEnabled = !timerEnabled;
                    timerOption.setSelected(timerEnabled);
                    if (!timerEnabled) {
                        selectedTime = 0;
                        for (auto& btn : timeButtons)
                            btn->setSelected(false);
                    }
                }

                if (timerEnabled) {
                    for (auto& btn : timeButtons) {
                        if (btn->isClicked(window)) {
                            for (auto& other : timeButtons)
                                other->setSelected(false);
                            btn->setSelected(true);
                            selectedTime = btn->getTime();
                        }
                    }
                }

                if (returnButton.isMouseOver(window))
                    return -1;

                if (startButton.isMouseOver(window)) {
                    if (!timerEnabled)
                        return 0;
                    if (selectedTime == 0)
                        continue;
                    return selectedTime;
                }
            }
        }

        for (auto& btn : timeButtons)
            btn->update(window);
        returnButton.update(window);
        timerOption.update(window);

        if (timerEnabled && selectedTime == 0) {
            startButton.getText().setFillColor(sf::Color(100, 100, 100));
        } else {
            startButton.update(window);
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        timerOption.draw(window);

        if (timerEnabled) {
            for (auto& btn : timeButtons)
                btn->draw(window);
        }

        returnButton.draw(window);
        startButton.draw(window);
        window.display();
    }

    return 0;
}
