#include <SFML/Graphics.hpp>
#include <iostream>

// Класс кнопки
class Button {
 private:
    sf::Text m_text;
    sf::FloatRect m_bounds;
    sf::Color m_hoverColor;
    sf::Color m_normalColor;

 public:
    Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& color,
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

    void draw(sf::RenderWindow& window) {
        window.draw(m_text);
    }

    bool isMouseOver(const sf::RenderWindow& window) const {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return m_bounds.contains(mousePos);
    }

    void update(const sf::RenderWindow& window) {
        if (isMouseOver(window)) {
            m_text.setFillColor(m_hoverColor);
        } else {
            m_text.setFillColor(m_normalColor);
        }
    }

    const sf::Text& getText() const { return m_text; }
};

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
    sf::Text title("Chess", font, 50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(250, 100);

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

// Функция для отображения шахматной доски (заглушка)
void showChessBoard(sf::RenderWindow& window) {
    // Здесь будет код для отображения шахматной доски
    sf::Font font;
    font.loadFromFile("../font/Tiny5-Regular.ttf");

    sf::Text text("Chess board", font, 30);
    text.setPosition(250, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Шахматы");

    // Показываем меню
    showMenu(window);

    // Если окно не закрыто (нажата кнопка Старт), показываем шахматную доску
    if (window.isOpen()) {
        showChessBoard(window);
    }

    return 0;
}
