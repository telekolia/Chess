// для отладки CheckmateDetector

#include <vector>

enum class PieceType : int {
    Pawn = 1,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
};

const char* chessTheme[12] = {"../res/chess_green/white_pawn.png",   "../res/chess_green/white_rook.png",  "../res/chess_green/white_knight.png",
                              "../res/chess_green/white_bishop.png", "../res/chess_green/white_queen.png", "../res/chess_green/white_king.png",
                              "../res/chess_green/black_pawn.png",   "../res/chess_green/black_rook.png",  "../res/chess_green/black_knight.png",
                              "../res/chess_green/black_bishop.png", "../res/chess_green/black_queen.png", "../res/chess_green/black_king.png"};
