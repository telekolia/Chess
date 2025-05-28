#include "Piece.hpp"

Piece::Piece() {
    m_type = 'P';
    m_playerColor = true;
    m_position = -1;
    m_moved = false;
}

Piece::Piece(char type, bool player, int pos, bool moved) : m_type(type), m_playerColor(player), m_position(-1), m_moved(true), enPassant(-1) {
}

void Piece::setPiece(char type, bool player, int pos, bool moved) {
    setType(type);
    setPlayer(player);
    setPosition(pos);  // m_moved true
    setMoved(moved);   // m_moved false
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

void Piece::move() {
    if (m_position <= -1 || 64 <= m_position) {
        m_position = -1;
        m_sprite.setColor(sf::Color(0, 0, 0));
        m_sprite.setPosition(sf::Vector2f((m_position % 8) * 88.f, (m_position / 8) * 88.f));
        possibleMoves.clear();
        m_moved = true;
    } else {
        m_sprite.setPosition(sf::Vector2f((m_position % 8) * 88.f, (m_position / 8) * 88.f));
        m_moved = true;
    }
    return;
}

void Piece::setTexture() {
    m_sprite = sf::Sprite();
    switch (m_type) {
        case 'P':
            m_texture = (m_playerColor ? PieceTextures::whitePawn : PieceTextures::blackPawn);
            m_textureToggled = (m_playerColor ? PieceTextures::whitePawnToggled : PieceTextures::blackPawnToggled);
            break;
        case 'R':
            m_texture = (m_playerColor ? PieceTextures::whiteRook : PieceTextures::blackRook);
            m_textureToggled = (m_playerColor ? PieceTextures::whiteRookToggled : PieceTextures::blackRookToggled);
            break;
        case 'H':
            m_texture = (m_playerColor ? PieceTextures::whiteKnight : PieceTextures::blackKnight);
            m_textureToggled = (m_playerColor ? PieceTextures::whiteKnightToggled : PieceTextures::blackKnightToggled);
            break;
        case 'B':
            m_texture = (m_playerColor ? PieceTextures::whiteBishop : PieceTextures::blackBishop);
            m_textureToggled = (m_playerColor ? PieceTextures::whiteBishopToggled : PieceTextures::blackBishopToggled);
            break;
        case 'Q':
            m_texture = (m_playerColor ? PieceTextures::whiteQueen : PieceTextures::blackQueen);
            m_textureToggled = (m_playerColor ? PieceTextures::whiteQueenToggled : PieceTextures::blackQueenToggled);
            break;
        case 'K':
            m_texture = (m_playerColor ? PieceTextures::whiteKing : PieceTextures::blackKing);
            m_textureToggled = (m_playerColor ? PieceTextures::whiteKingToggled : PieceTextures::blackKingToggled);
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

void Piece::toggle() {
    isToggled = !isToggled;
    if (isToggled) {
        m_sprite.setTexture(m_textureToggled);
    } else {
        m_sprite.setTexture(m_texture);
    }
}
