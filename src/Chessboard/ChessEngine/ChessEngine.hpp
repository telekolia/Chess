#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "../Piece/Piece.hpp"

class ChessEngine: public sf::Drawable{
private:
    std::array<Piece, 16> whitePieces;
    std::array<Piece, 16> blackPieces;
    Piece* selectedPiece;
    std::vector<sf::CircleShape> possibleMovesCircules;
    std::string lastMove;

    sf::Font font;
    sf::Text textTurn;
    sf::Text textSituation;


    bool selected;
    bool playerTurn; // true = White turn, false = Black Turn
    bool playerTurnCheck;
    bool mate;
    int turn;

    void createMovesCircules();

    void generatePossibleMoves();

    void generatePawnMoves(Piece* tmpPiece);
    void generateRookMoves(Piece* tmpPiece);
    void generateKnightMoves(Piece* tmpPiece);
    void generateBishopMoves(Piece* tmpPiece);
    void generateQueenMoves(Piece* tmpPiece);
    void generateKingMoves(Piece* tmpPiece);
    void generateCastling(Piece* tmpPiece); // Рокировка

    void eraseMoves(Piece* tmpPiece);

    void checkMate();

    void updateInfo();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    ChessEngine();

    bool getSelected(){return selected;}

    bool getMate(){return mate;}

    bool selectPiece(int pos);

    void moveSelected(int pos);

    void restart();

    bool getPlayerturn(){return playerTurn;};

    int getTurn() { return turn; };

};
