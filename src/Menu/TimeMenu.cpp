#include "TimeMenu.hpp"

int showTimeMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../font/Tiny5-Regular.ttf")) {
        return 0;
    }

    sf::Text title("Game Settings", font, 50);
    title.setFillColor(sf::Color::Yellow);
    sf::FloatRect titleBounds = title.getGlobalBounds();
    title.setPosition((1080 - titleBounds.width) / 2.f, 50);

    sf::Text timerLabel("Timer", font, 30);
    timerLabel.setFillColor(sf::Color::White);
    timerLabel.setPosition(100, 150);

    sf::CircleShape timerCircle(10);
    timerCircle.setPosition(60, 157);
    timerCircle.setFillColor(sf::Color::Transparent);
    timerCircle.setOutlineColor(sf::Color::White);
    timerCircle.setOutlineThickness(2);

    bool timerEnabled = false;
    int selectedTime = 0;

    std::vector<std::shared_ptr<TimeOption<int>>> timeButtons = {
        std::make_shared<TimeOption<int>>(60, font, sf::Vector2f(300, 230)),
        std::make_shared<TimeOption<int>>(30, font, sf::Vector2f(300, 280)),
        std::make_shared<TimeOption<int>>(15, font, sf::Vector2f(300, 330)),
        std::make_shared<TimeOption<int>>(5, font, sf::Vector2f(500, 230)),
        std::make_shared<TimeOption<int>>(3, font, sf::Vector2f(500, 280)),
        std::make_shared<TimeOption<int>>(1, font, sf::Vector2f(500, 330)),
    };

    Button returnButton("Return", font, 28, sf::Vector2f(30, 660), sf::Color::White, sf::Color::Red);
    Button startButton("Start", font, 28, sf::Vector2f(920, 660), sf::Color::White, sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (timerCircle.getGlobalBounds().contains(mousePos)) {
                    timerEnabled = !timerEnabled;
                    if (!timerEnabled) {
                        selectedTime = 0;
                        for (auto& btn : timeButtons) btn->setSelected(false);
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

                // Кнопка Return
                if (returnButton.isMouseOver(window))
                    return -1;

                // Кнопка Start
                if (startButton.isMouseOver(window)) {
                    if (!timerEnabled) return 0;
                    if (timerEnabled && selectedTime == 0) continue;
                    return selectedTime;
                }
            }
        }

        for (auto& btn : timeButtons) btn->update(window);
        returnButton.update(window);

        if (timerEnabled && selectedTime == 0) {
            startButton.getText().setFillColor(sf::Color(100, 100, 100)); 
        } else {
            startButton.update(window);
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(timerLabel);

        // Жёлтый кружок если активен
        if (timerEnabled) {
            sf::CircleShape fill(6);
            fill.setFillColor(sf::Color::Yellow);
            fill.setPosition(timerCircle.getPosition().x + 4, timerCircle.getPosition().y + 4);
            window.draw(timerCircle);
            window.draw(fill);
        } else {
            timerCircle.setFillColor(sf::Color::Transparent);
            window.draw(timerCircle);
        }

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
