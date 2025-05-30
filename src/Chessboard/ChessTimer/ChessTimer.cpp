#include "ChessTimer.hpp"

ChessTimer::ChessTimer(int gameLatensy, sf::Font font) {
    this->font = font;
    secondsWhitePlayer = gameLatensy*60;
    secondsBlackPlayer = gameLatensy*60;
    tmpsecondsWhitePlayer = secondsWhitePlayer;
    tmpsecondsBlackPlayer = secondsBlackPlayer;

    timerInfo.setFillColor(sf::Color::Green);
    timerInfo.setScale(340.f, 100.f);
    timerInfo.setPosition(730.f, 100.f);

    whiteTimerText.setFont(this->font);
    whiteTimerText.setString("00:00");
    whiteTimerText.setCharacterSize(32);
    whiteTimerText.setFillColor(sf::Color::White);
    whiteTimerText.setPosition(850, 40);

    blackTimerText.setFont(this->font);
    blackTimerText.setString("00:00");
    blackTimerText.setCharacterSize(32);
    blackTimerText.setFillColor(sf::Color::Black);
    blackTimerText.setPosition(850, 80);

    textUpdate();
}

void ChessTimer::TimeUpdate(int turn, bool playerTurn) {
    // Возвращает время прошедшее за время работы цикла отрисовки и снова начинает отсчитывать время цикла
    sf::Time time = clock.restart();

    if (turn > 2) {
        if (playerTurn){
            if (tmpsecondsWhitePlayer > 0){
                tmpsecondsWhitePlayer -= time.asSeconds();

                // if (static_cast<int>(tmpsecondsWhitePlayer) % 60 < 10){
                //     stringSeconds1 = "0"+stringSeconds1;
                // }

                whiteTimerSring = std::to_string(static_cast<int>(tmpsecondsWhitePlayer) / 60) + ":" + std::to_string(static_cast<int>(tmpsecondsWhitePlayer) % 60);

                if (tmpsecondsWhitePlayer <=0){
                    whiteTimerSring="00:00";
                }

                whiteTimerText.setString(whiteTimerSring);
            }
        }
        else{
            if (tmpsecondsBlackPlayer > 0){
                tmpsecondsBlackPlayer -= time.asSeconds();

                // if (static_cast<int>(tmpsecondsWhitePlayer) % 60 < 10){
                //     stringSeconds1 = "0"+stringSeconds1;
                // }

                blackTimerSring = std::to_string(static_cast<int>(tmpsecondsBlackPlayer) / 60) + ":" + std::to_string(static_cast<int>(tmpsecondsBlackPlayer) % 60);

                if (tmpsecondsBlackPlayer <=0){
                    blackTimerSring = "00:00";
                }

                blackTimerText.setString(blackTimerSring);
            }
        }
    }
}

void ChessTimer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(timerInfo);
    target.draw(whiteTimerText);
    target.draw(blackTimerText);
}

void ChessTimer::restart() {
    tmpsecondsBlackPlayer = secondsBlackPlayer;
    tmpsecondsWhitePlayer = secondsWhitePlayer;

    textUpdate();
}

void ChessTimer::textUpdate() {
    whiteTimerSring = std::to_string(static_cast<int>(tmpsecondsWhitePlayer) / 60) + ":" + std::to_string(static_cast<int>(tmpsecondsWhitePlayer) % 60);
    whiteTimerText.setString(whiteTimerSring);

    blackTimerSring = std::to_string(static_cast<int>(tmpsecondsBlackPlayer) / 60) + ":" + std::to_string(static_cast<int>(tmpsecondsBlackPlayer) % 60);
    blackTimerText.setString(blackTimerSring);
}
