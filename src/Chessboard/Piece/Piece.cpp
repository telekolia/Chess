#include "Piece.hpp"

const char* chessTheme[12] = {"../res/chess_green/white_pawn.png",   "../res/chess_green/white_rook.png",  "../res/chess_green/white_knight.png",
                              "../res/chess_green/white_bishop.png", "../res/chess_green/white_queen.png", "../res/chess_green/white_king.png",
                              "../res/chess_green/black_pawn.png",   "../res/chess_green/black_rook.png",  "../res/chess_green/black_knight.png",
                              "../res/chess_green/black_bishop.png", "../res/chess_green/black_queen.png", "../res/chess_green/black_king.png"};

const char* chessThemeToggled[12] = {"../res/chess/white_pawn.png",   "../res/chess/white_rook.png",  "../res/chess/white_knight.png",
                                     "../res/chess/white_bishop.png", "../res/chess/white_queen.png", "../res/chess/white_king.png",
                                     "../res/chess/black_pawn.png",   "../res/chess/black_rook.png",  "../res/chess/black_knight.png",
                                     "../res/chess/black_bishop.png", "../res/chess/black_queen.png", "../res/chess/black_king.png"};

Piece::Piece(char type, bool player, int pos, bool moved)
        : m_type(type), m_playerColor(player), m_position(-1), m_moved(true), enPassant(-1) {}

void Piece::setPiece(char type, bool player, int pos, bool moved){
    setType(type);
    setPlayer(player);
    setPosition(pos); //m_moved true
    setMoved(moved); // m_moved false
}

void Piece::setType(char ch) {
    m_type = ch;
    setTexture();
}

void Piece::setPlayer(bool bl) {
        m_playerColor = bl;
        setTexture();
    }

void Piece::setPosition(int pos) {
    m_position = pos;
    move();
}

void Piece::move(){
    if(m_position<=-1 || 64<=m_position){
        m_position = -1;
        m_sprite.setColor(sf::Color(0, 0, 0));
        m_sprite.setPosition(sf::Vector2f((m_position % 8) * 64.f + 32.f, (m_position / 8) * 64.f + 32.f));
        possibleMoves.clear();
        m_moved = true;
    }
    else{
        m_sprite.setPosition(sf::Vector2f((m_position % 8) * 64.f + 32.f, (m_position / 8) * 64.f + 32.f));
        m_moved = true;
    }
    return;
}

void Piece::setTexture(){
    m_sprite = sf::Sprite();
    switch (m_type)
    {
        case 'P':
            m_texture.loadFromFile(m_playerColor ? chessTheme[1] : chessTheme[7]);
            m_textureToggled.loadFromFile(m_playerColor ? chessThemeToggled[1] : chessThemeToggled[7]);
            break;
        case 'R':
            m_texture.loadFromFile(m_playerColor ? chessTheme[2] : chessTheme[8]);
            m_textureToggled.loadFromFile(m_playerColor ? chessThemeToggled[2] : chessThemeToggled[8]);
            break;
        case 'H':
            m_texture.loadFromFile(m_playerColor ? chessTheme[3] : chessTheme[9]);
            m_textureToggled.loadFromFile(m_playerColor ? chessThemeToggled[3] : chessThemeToggled[9]);
            break;
        case 'B':
            m_texture.loadFromFile(m_playerColor ? chessTheme[4] : chessTheme[10]);
            m_textureToggled.loadFromFile(m_playerColor ? chessThemeToggled[4] : chessThemeToggled[10]);
            break;
        case 'Q':
            m_texture.loadFromFile(m_playerColor ? chessTheme[5] : chessTheme[11]);
            m_textureToggled.loadFromFile(m_playerColor ? chessThemeToggled[5] : chessThemeToggled[11]);
            break;
        case 'K':
            m_texture.loadFromFile(m_playerColor ? chessTheme[6] : chessTheme[12]);
            m_textureToggled.loadFromFile(m_playerColor ? chessThemeToggled[6] : chessThemeToggled[12]);
            break;
        default:
            std::cerr << "Неверный тип фигуры\n";
            break;
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(sf::Vector2f(4.f, 4.f));
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
