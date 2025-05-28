#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "PieceTextures.hpp"

class Piece : public sf::Drawable {
 private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Texture m_textureToggled;
    std::vector<int> possibleMoves;
    std::vector<int> dangerMoves;  // Ходы, при которых вражеский король будет атакован

    char m_type;     //'K' == Король, 'Q' == Королева, 'R' == Ладья, 'B' == Слон, 'H' = Конь, 'P' == Пешка
    bool m_playerColor;   // true == Белый , false == Чёрный
    int m_position;  // 0-63 клетка на доске, -1 съеден
    int enPassant; // Речь о взятии на проходе
    bool m_moved; // Двигалась ли фигура с начала игры
    bool isToggled = false;

    void setTexture();
    void move();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 public:
    Piece();
    Piece(char type , bool player, int pos, bool moved = false);

    void setPiece(char type, bool player, int pos, bool moved = false);

    void setType(char ch);
    void setPlayer(bool bl);
    void setPosition(int pos);
    void setMoved(bool moved) { m_moved = moved; }
    void setEnPassant(int x) { enPassant = x; }

    char getType() { return m_type; }
    bool getPlayer() { return m_playerColor; }
    int getPosition() { return m_position; }
    bool getMoved() { return m_moved; }
    int getEnPassant() { return enPassant; }
    std::vector<int>& getPossibleMoves() { return possibleMoves; }
    std::vector<int>& getDangerMoves() { return dangerMoves; }

    void toggle();
};
