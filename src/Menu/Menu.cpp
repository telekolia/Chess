#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Interface/Button.hpp"

void showMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../font/Tiny5-Regular.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        return;
    }

    float centerX = 1080 / 2.f;

    Button startButton("Start", font, 30, sf::Vector2f(centerX - 50, 250), sf::Color::White, sf::Color::Green);
    Button exitButton("Exit", font, 30, sf::Vector2f(centerX - 50, 350), sf::Color::White, sf::Color::Red);

    sf::Text title("Chess", font, 70);
    title.setFillColor(sf::Color::Yellow);

    sf::FloatRect titleBounds = title.getGlobalBounds();
    title.setPosition((1080 - titleBounds.width) / 2.f, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Обработка нажатия кнопок
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startButton.isMouseOver(window)) {
                        return;
                    } else if (exitButton.isMouseOver(window)) {
                        window.close();
                    }
                }
            }
        }

        // Обновление состояния кнопок
        startButton.update(window);
        exitButton.update(window);

        // Отрисовка
        window.clear(sf::Color::Black);
        window.draw(title);
        startButton.draw(window);
        exitButton.draw(window);
        window.display();
    }
}
