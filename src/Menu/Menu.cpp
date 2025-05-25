#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Interface/Button.hpp"

// Функция для создания меню
void showMenu(sf::RenderWindow& window) {
    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("../font/Tiny5-Regular.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        return;
    }

    // Создание кнопок
    Button startButton("Start", font, 30, sf::Vector2f(300, 200), sf::Color::White, sf::Color::Green);
    Button exitButton("Exit", font, 30, sf::Vector2f(300, 300), sf::Color::White, sf::Color::Red);

    // Текст заголовка
    sf::Text title("Chess by Telekolia 8)", font, 50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(250, 100);

    // Так называемый "game loop"
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
                        return;  // Выход из меню (переход к игре)
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
