#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class PieceTextures{
public:
    static sf::Texture blackKing;
    static sf::Texture blackQueen;
    static sf::Texture blackRook;
    static sf::Texture blackKnight;
    static sf::Texture blackBishop;
    static sf::Texture blackPawn;

    static sf::Texture whiteKing;
    static sf::Texture whiteQueen;
    static sf::Texture whiteRook;
    static sf::Texture whiteKnight;
    static sf::Texture whiteBishop;
    static sf::Texture whitePawn;

    static sf::Texture blackKingToggled;
    static sf::Texture blackQueenToggled;
    static sf::Texture blackRookToggled;
    static sf::Texture blackKnightToggled;
    static sf::Texture blackBishopToggled;
    static sf::Texture blackPawnToggled;

    static sf::Texture whiteKingToggled;
    static sf::Texture whiteQueenToggled;
    static sf::Texture whiteRookToggled;
    static sf::Texture whiteKnightToggled;
    static sf::Texture whiteBishopToggled;
    static sf::Texture whitePawnToggled;

    static sf::Texture loadTexture(std::string str);
};
