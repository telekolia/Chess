#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ChessTimer : public sf::Drawable {
    private:
     sf::Clock clock;

     int secondsWhitePlayer;
     int secondsBlackPlayer;

     float tmpsecondsWhitePlayer;
     float tmpsecondsBlackPlayer;

     sf::RectangleShape timerInfo;
     sf::String whiteTimerSring, blackTimerSring;
     sf::Text whiteTimerText, blackTimerText;
     sf::Font font;

     void textUpdate();

     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
     ChessTimer(sf::Font font);
     ChessTimer(int gameLatensy, sf::Font font);
     void TimeUpdate (int turn, bool playerTurn);
     void restart();
};
