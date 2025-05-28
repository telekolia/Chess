#include "PieceTextures.hpp"

sf::Texture PieceTextures::loadTexture(std::string str){
    sf::Texture tmp;
    if (!tmp.loadFromFile(str))
        std::cout << "Error loading file\n";
    return tmp;
}

sf::Texture PieceTextures::blackKing = PieceTextures::loadTexture("../res/chess_green/black_king.png");
sf::Texture PieceTextures::blackQueen = PieceTextures::loadTexture("../res/chess_green/black_queen.png");
sf::Texture PieceTextures::blackRook = PieceTextures::loadTexture("../res/chess_green/black_rook.png");
sf::Texture PieceTextures::blackKnight = PieceTextures::loadTexture("../res/chess_green/black_knight.png");
sf::Texture PieceTextures::blackBishop = PieceTextures::loadTexture("../res/chess_green/black_bishop.png");
sf::Texture PieceTextures::blackPawn = PieceTextures::loadTexture("../res/chess_green/black_pawn.png");

sf::Texture PieceTextures::whiteKing = PieceTextures::loadTexture("../res/chess_green/white_king.png");
sf::Texture PieceTextures::whiteQueen = PieceTextures::loadTexture("../res/chess_green/white_queen.png");
sf::Texture PieceTextures::whiteRook = PieceTextures::loadTexture("../res/chess_green/white_rook.png");
sf::Texture PieceTextures::whiteKnight = PieceTextures::loadTexture("../res/chess_green/white_knight.png");
sf::Texture PieceTextures::whiteBishop = PieceTextures::loadTexture("../res/chess_green/white_bishop.png");
sf::Texture PieceTextures::whitePawn = PieceTextures::loadTexture("../res/chess_green/white_pawn.png");

sf::Texture PieceTextures::blackKingToggled = PieceTextures::loadTexture("../res/chess_green/black_king.png");
sf::Texture PieceTextures::blackQueenToggled = PieceTextures::loadTexture("../res/chess_green/black_queen.png");
sf::Texture PieceTextures::blackRookToggled = PieceTextures::loadTexture("../res/chess_green/black_rook.png");
sf::Texture PieceTextures::blackKnightToggled = PieceTextures::loadTexture("../res/chess_green/black_knight.png");
sf::Texture PieceTextures::blackBishopToggled = PieceTextures::loadTexture("../res/chess_green/black_bishop.png");
sf::Texture PieceTextures::blackPawnToggled = PieceTextures::loadTexture("../res/chess_green/black_pawn.png");

sf::Texture PieceTextures::whiteKingToggled = PieceTextures::loadTexture("../res/chess_green/white_king.png");
sf::Texture PieceTextures::whiteQueenToggled = PieceTextures::loadTexture("../res/chess_green/white_queen.png");
sf::Texture PieceTextures::whiteRookToggled = PieceTextures::loadTexture("../res/chess_green/white_rook.png");
sf::Texture PieceTextures::whiteKnightToggled = PieceTextures::loadTexture("../res/chess_green/white_knight.png");
sf::Texture PieceTextures::whiteBishopToggled = PieceTextures::loadTexture("../res/chess_green/white_bishop.png");
sf::Texture PieceTextures::whitePawnToggled = PieceTextures::loadTexture("../res/chess_green/white_pawn.png");
