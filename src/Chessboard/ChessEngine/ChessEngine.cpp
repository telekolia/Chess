#include "../ChessEngine/ChessEngine.hpp"
// Часть кода была взаимствована

ChessEngine::ChessEngine() : board() {
    font.loadFromFile("../font/Tiny5-Regular.ttf");

    textSituation.setFont(font);
    textSituation.setCharacterSize(48);
    textSituation.setStyle(sf::Text::Bold);
    textSituation.setFillColor(sf::Color::White);
    textSituation.setPosition(750.f, 110.f);
    restart();
}

void ChessEngine::restart() {
    selected = false;
    playerTurn = true;  // Начинает белый
    playerTurnCheck = false;
    mate = false;
    turn = 1;

    blackPieces[7].setPiece('R', false, 0);
    blackPieces[6].setPiece('H', false, 1);
    blackPieces[5].setPiece('B', false, 2);
    blackPieces[4].setPiece('Q', false, 3);
    blackPieces[3].setPiece('K', false, 4);
    blackPieces[2].setPiece('B', false, 5);
    blackPieces[1].setPiece('H', false, 6);
    blackPieces[0].setPiece('R', false, 7);

    whitePieces[0].setPiece('R', true, 56);
    whitePieces[1].setPiece('H', true, 57);
    whitePieces[2].setPiece('B', true, 58);
    whitePieces[3].setPiece('Q', true, 59);
    whitePieces[4].setPiece('K', true, 60);
    whitePieces[5].setPiece('B', true, 61);
    whitePieces[6].setPiece('H', true, 62);
    whitePieces[7].setPiece('R', true, 63);

    for (int i = 8; i < 16; ++i) {
        whitePieces[i].setPiece('P', true, 48 + (i - 8));
        blackPieces[i].setPiece('P', false, 8 + (i - 8));
    }

    generatePossibleMoves();
}

void ChessEngine::updateInfo() {
    if (!mate) {
        if (playerTurn)
            textSituation.setString("White's Turn");
        else
            textSituation.setString("Blacks's Turn");

        if (playerTurnCheck)
            textSituation.setString(textSituation.getString() + "\nCheck");
    } else {
        if (playerTurnCheck) {
            if (playerTurn)
                textSituation.setString("CHECKMATE\nBlack Wins");
            else
                textSituation.setString("CHECKMATE\nWhite Wins");
        } else {
            textSituation.setString("STALEMATE\nIts a DRAW");
        }
    }
}

// Не перепутайте со смыслом "ничья", тут перегружаем функцию рисовщика SFML, чтобы удобно рисовать игру одной коммандой
void ChessEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(board);
    target.draw(textSituation);

    for (int i = 0; i < 16; i++) {
        target.draw(whitePieces[i]);
        target.draw(blackPieces[i]);
    }

    if (selectedPiece != nullptr && selected) {
        for (int i = 0; i < possibleMovesCircules.size(); i++) {
            target.draw(possibleMovesCircules.at(i));
        }
    }
}

void ChessEngine::createMovesCircules() {
    if (selectedPiece == nullptr) {
        return;
    }

    possibleMovesCircules.clear();

    for (int i = 0; i < selectedPiece->getPossibleMoves().size(); i++) {
        sf::CircleShape tmp;
        tmp.setPosition(sf::Vector2f((selectedPiece->getPossibleMoves().at(i) % 8) * 88.f, (selectedPiece->getPossibleMoves().at(i) / 8) * 88.f));
        tmp.setRadius(11.f);
        tmp.setFillColor(sf::Color::Cyan);
        possibleMovesCircules.push_back(tmp);
    }
}

bool ChessEngine::selectPiece(int pos) {
    for (int i = 0; i < 16; ++i) {
        if (playerTurn) {  // Ход белого
            if (whitePieces[i].getPosition() == pos) {
                selectedPiece = &whitePieces[i];
                selected = true;
                break;
            }
        } else {  // Ход чёрного
            if (blackPieces[i].getPosition() == pos) {
                selectedPiece = &blackPieces[i];
                selected = true;
                break;
            }
        }
        selected = false;
    }

    if (!selected) {
        selectedPiece = NULL;
        possibleMovesCircules.clear();
        return selected;
    }

    createMovesCircules();

    return selected;
}

void ChessEngine::moveSelected(int pos) {
    bool validMove{false};

    if ((selectedPiece == nullptr) || !selected) {
        return;
    }

    // Check pos with the Piece's possibleMoves
    for (int i = 0; i < selectedPiece->getPossibleMoves().size(); ++i) {
        if (pos == selectedPiece->getPossibleMoves().at(i)) {
            validMove = true;
            break;
        }
    }

    if (validMove) {
        // Если выполняем ракеровку
        if ((selectedPiece->getType() == 'K') && (!selectedPiece->getMoved())) {
            if (selectedPiece->getPlayer()) {  // If white
                // whitePieces[0] Bot Left Rook, whitePieces[7] Bot Right Rook
                if (pos == 62)
                    whitePieces[7].setPosition(61);
                else if (pos == 58)
                    whitePieces[0].setPosition(59);
            } else {  // If Black
                // blackPieces[7] Top Left Rook, blackPieces[0] Top Right Rook
                if (pos == 6)
                    blackPieces[0].setPosition(5);
                else if (pos == 2)
                    blackPieces[7].setPosition(3);
            }
        }

        // Если пешка сделала длинный шаг
        // White pawn -16, Black pawn +16
        if ((selectedPiece->getType() == 'P')) {
            if (!selectedPiece->getMoved()) {
                if (pos == (selectedPiece->getPosition() - 16)) {
                    selectedPiece->setEnPassant(selectedPiece->getPosition() - 8);
                } else if (pos == (selectedPiece->getPosition() + 16)) {
                    selectedPiece->setEnPassant(selectedPiece->getPosition() + 8);
                }
            } else {
                for (int i = 0; i < 16; i++) {
                    if (playerTurn) {
                        if (pos == blackPieces[i].getEnPassant())
                            blackPieces[i].setPosition(pos);
                    } else {
                        if (pos == whitePieces[i].getEnPassant())
                            whitePieces[i].setPosition(pos);
                    }
                }
            }
        }
        if (selectedPiece->getMoved()) {
            for (int i = 0; i < 16; i++) {
                whitePieces[i].setEnPassant(-1);
                blackPieces[i].setEnPassant(-1);
            }
        }

        selectedPiece->setPosition(pos);

        for (int i = 0; i < 16; i++) {
            if (selectedPiece->getPlayer()) {  // Если белые
                if (blackPieces[i].getPosition() == pos) {
                    blackPieces[i].setPosition(-1);
                    break;
                }
            } else {  // Если чёрные
                if (whitePieces[i].getPosition() == pos) {
                    whitePieces[i].setPosition(-1);
                    break;
                }
            }
        }

        if (playerTurnCheck) {
            playerTurnCheck = false;
        }

        playerTurn = !playerTurn;  // Смена хода
        generatePossibleMoves();
    }

    selectedPiece = NULL;
    selected = false;
}

void ChessEngine::generatePossibleMoves() {
    Piece* tmpPiece;

    // Повторяем для каждой фигуры
    for (int x = 0; x < 32; x++) {
        if (x < 16)
            tmpPiece = &whitePieces[x];
        else
            tmpPiece = &blackPieces[x - 16];
        tmpPiece->getPossibleMoves().clear();
        tmpPiece->getDangerMoves().clear();

        if (tmpPiece->getPosition() == -1)
            continue;

        // Генерируем ходя для фигуры нужного типа
        switch (tmpPiece->getType()) {
            case 'K':
                generateKingMoves(tmpPiece);
                break;
            case 'Q':
                generateQueenMoves(tmpPiece);
                break;
            case 'R':
                generateRookMoves(tmpPiece);
                break;
            case 'B':
                generateBishopMoves(tmpPiece);
                break;
            case 'H':
                generateKnightMoves(tmpPiece);
                break;
            case 'P':
                generatePawnMoves(tmpPiece);
                break;
            default:
                std::cerr << "Error piece type does not exist.\n";
                break;
        }
    }

    // Удаляем ходы поверх союзных фигур
    for (int x = 0; x < 16; x++) {
        if (playerTurn) {
            eraseMoves(&whitePieces[x]);
        } else {
            eraseMoves(&blackPieces[x]);
        }
    }

    checkMate();

    updateInfo();
    turn++;
}

void ChessEngine::eraseMoves(Piece* tmpPiece) {
    if (tmpPiece->getPosition() == -1)
        return;

    if (tmpPiece->getPlayer() == playerTurn) {
        // Удаляем ходы поверх союзных фигур

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < tmpPiece->getPossibleMoves().size(); j++) {
                if (tmpPiece->getPlayer()) {  // White
                    if (tmpPiece->getPossibleMoves().at(j) == whitePieces[i].getPosition()) {
                        tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j);
                        break;
                    }
                } else {  // Black
                    if (tmpPiece->getPossibleMoves().at(j) == blackPieces[i].getPosition()) {
                        tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j);
                        break;
                    }
                }
            }
        }

        // Удаляем ходы, короля на атакованные клетки
        if (tmpPiece->getType() == 'K') {
            for (int j = 0; j < tmpPiece->getPossibleMoves().size(); j++) {
                for (int i = 0; i < 16; i++) {
                    int o{0};
                    if (tmpPiece->getPlayer()) {  // White
                        for (o = 0; o < blackPieces[i].getPossibleMoves().size(); o++) {
                            if (tmpPiece->getPossibleMoves().at(j) == blackPieces[i].getPossibleMoves().at(o)) {
                                tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j--);
                                break;
                            }
                        }
                        if ((o != blackPieces[i].getPossibleMoves().size()))
                            break;
                        ;
                    } else {  // Black
                        for (o = 0; o < whitePieces[i].getPossibleMoves().size(); o++) {
                            if (tmpPiece->getPossibleMoves().at(j) == whitePieces[i].getPossibleMoves().at(o)) {
                                tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j--);
                                break;
                            }
                        }
                        if ((o != whitePieces[i].getPossibleMoves().size()))
                            break;
                        ;
                    }
                }
            }
        }

        // Убираем ходы, которые подставляют короля игрока под шах
        if (tmpPiece->getType() != 'K') {
            for (int i = 0; i < 16; i++) {
                if (playerTurn && (blackPieces[i].getDangerMoves().size() > 1)) {
                    for (int j = 0; j < blackPieces[i].getDangerMoves().size(); j++) {
                        if (blackPieces[i].getDangerMoves().at(j) == tmpPiece->getPosition()) {
                            std::vector<int> tmpMoves;
                            for (int x = 0; x < tmpPiece->getPossibleMoves().size(); x++) {
                                for (int k = 0; k < blackPieces[i].getDangerMoves().size(); k++) {
                                    if (tmpPiece->getPossibleMoves().at(x) == blackPieces[i].getDangerMoves().at(k))
                                        tmpMoves.push_back(tmpPiece->getPossibleMoves().at(x));
                                }
                            }
                            tmpPiece->getPossibleMoves().clear();
                            tmpPiece->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                } else if (!playerTurn && (whitePieces[i].getDangerMoves().size() > 1)) {
                    for (int j = 0; j < whitePieces[i].getDangerMoves().size(); j++) {
                        if (whitePieces[i].getDangerMoves().at(j) == tmpPiece->getPosition()) {
                            std::vector<int> tmpMoves;
                            for (int x = 0; x < tmpPiece->getPossibleMoves().size(); x++) {
                                for (int k = 0; k < whitePieces[i].getDangerMoves().size(); k++) {
                                    if (tmpPiece->getPossibleMoves().at(x) == whitePieces[i].getDangerMoves().at(k))
                                        tmpMoves.push_back(tmpPiece->getPossibleMoves().at(x));
                                }
                            }
                            tmpPiece->getPossibleMoves().clear();
                            tmpPiece->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void ChessEngine::generateKingMoves(Piece* tmpPiece) {
    int piecePos{tmpPiece->getPosition()};
    tmpPiece->getPossibleMoves().clear();

    if ((piecePos / 8) != 0) {
        tmpPiece->getPossibleMoves().push_back(piecePos - 8);
        if ((piecePos % 8) != 0)
            tmpPiece->getPossibleMoves().push_back(piecePos - 9);
        if ((piecePos % 8) != 7)
            tmpPiece->getPossibleMoves().push_back(piecePos - 7);
    }
    if ((piecePos / 8) != 7) {
        tmpPiece->getPossibleMoves().push_back(piecePos + 8);
        if ((piecePos % 8) != 0)
            tmpPiece->getPossibleMoves().push_back(piecePos + 7);
        if ((piecePos % 8) != 7)
            tmpPiece->getPossibleMoves().push_back(piecePos + 9);
    }
    if ((piecePos % 8) != 0)
        tmpPiece->getPossibleMoves().push_back(piecePos - 1);
    if ((piecePos % 8) != 7)
        tmpPiece->getPossibleMoves().push_back(piecePos + 1);

    // generateCastling(tmpPiece);
}

void ChessEngine::generateQueenMoves(Piece* tmpPiece) {
    int piecePos{tmpPiece->getPosition()};
    int posCounter{1};

    bool dangerMove{false};
    bool finishLoop{false};

    tmpPiece->getPossibleMoves().clear();
    tmpPiece->getDangerMoves().clear();

    // Королева движется влево
    while (((piecePos - posCounter) >= 0) && ((piecePos / 8) == ((piecePos - posCounter) / 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 1;
    }

    // Королева движется вправо
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 1;
    while ((piecePos / 8) == ((piecePos + posCounter) / 8)) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 1;
    }
    // Королева движется вверх
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos - posCounter) >= 0) && (posCounter < 64) && ((piecePos % 8) == ((piecePos - posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }
    // Королева движется вниз
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos + posCounter) <= 63) && (posCounter < 64) && ((piecePos % 8) == ((piecePos + posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }
    // Королева движется вверх влево
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }
    // Королева движется вниз вправо
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }
    // Королева движется вверх вправо
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }
    // Королева движется вниз влево
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();

    if (!tmpPiece->getDangerMoves().empty()) {
        int collisions{0};
        for (int j = 0; j < tmpPiece->getDangerMoves().size(); j++) {
            for (int i = 0; i < 16; i++) {
                if (tmpPiece->getDangerMoves().at(j) == blackPieces[i].getPosition()) {
                    collisions++;
                    if (!tmpPiece->getPlayer())
                        collisions++;
                }
                if (tmpPiece->getDangerMoves().at(j) == whitePieces[i].getPosition()) {
                    collisions++;
                    if (tmpPiece->getPlayer())
                        collisions++;
                }
            }
        }

        if (collisions > 2)
            tmpPiece->getDangerMoves().clear();
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());
}

void ChessEngine::generateRookMoves(Piece* tmpPiece) {
    int piecePos = tmpPiece->getPosition();
    int posCounter{1};

    bool dangerMove{false};
    bool finishLoop{false};

    tmpPiece->getPossibleMoves().clear();
    tmpPiece->getDangerMoves().clear();

    // Ладья движется влево
    while (((piecePos - posCounter) >= 0) && ((piecePos / 8) == ((piecePos - posCounter) / 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 1;
    }

    // Ладья движется вправо
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 1;
    while ((piecePos / 8) == ((piecePos + posCounter) / 8)) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 1;
    }

    // Ладья движется вверх
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos - posCounter) >= 0) && (posCounter < 64) && ((piecePos % 8) == ((piecePos - posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }

    // Ладья движется вниз
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos + posCounter) <= 63) && (posCounter < 64) && ((piecePos % 8) == ((piecePos + posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }

    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();

    if (!tmpPiece->getDangerMoves().empty()) {
        int collisions{0};
        for (int j = 0; j < tmpPiece->getDangerMoves().size(); j++) {
            for (int i = 0; i < 16; i++) {
                if (tmpPiece->getDangerMoves().at(j) == blackPieces[i].getPosition()) {
                    collisions++;
                    if (!tmpPiece->getPlayer())
                        collisions++;
                }
                if (tmpPiece->getDangerMoves().at(j) == whitePieces[i].getPosition()) {
                    collisions++;
                    if (tmpPiece->getPlayer())
                        collisions++;
                }
            }
        }

        if (collisions > 2)
            tmpPiece->getDangerMoves().clear();
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());
}

void ChessEngine::generateBishopMoves(Piece* tmpPiece) {
    // Normal Bishop Moving
    int piecePos{tmpPiece->getPosition()};
    int posCounter{9};

    bool dangerMove{false};
    bool finishLoop{false};

    tmpPiece->getPossibleMoves().clear();
    tmpPiece->getDangerMoves().clear();

    // Слон движется вверх влево
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    // Слон движется вниз вправо
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    // Слон движется вверх вправо
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!playerTurn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    // Слон движется вниз влево
    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] это белый король , blackPieces[3] это чёрный король
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!playerTurn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            } else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    if (!dangerMove)
        tmpPiece->getDangerMoves().clear();

    if (!tmpPiece->getDangerMoves().empty()) {
        int collisions{0};
        for (int j = 0; j < tmpPiece->getDangerMoves().size(); j++) {
            for (int i = 0; i < 16; i++) {
                if (tmpPiece->getDangerMoves().at(j) == blackPieces[i].getPosition()) {
                    collisions++;
                    if (!tmpPiece->getPlayer())
                        collisions++;
                }
                if (tmpPiece->getDangerMoves().at(j) == whitePieces[i].getPosition()) {
                    collisions++;
                    if (tmpPiece->getPlayer())
                        collisions++;
                }
            }
        }

        if (collisions > 2)
            tmpPiece->getDangerMoves().clear();
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());
}

void ChessEngine::generateKnightMoves(Piece* tmpPiece) {
    tmpPiece->getPossibleMoves().clear();

    int piecePos{tmpPiece->getPosition()};

    if ((piecePos / 8) != 0) {
        if ((piecePos % 8) >= 2)
            tmpPiece->getPossibleMoves().push_back(piecePos - 10);
        if ((piecePos % 8) <= 5)
            tmpPiece->getPossibleMoves().push_back(piecePos - 6);
        if ((piecePos / 8) != 1) {
            if ((piecePos % 8) >= 1)
                tmpPiece->getPossibleMoves().push_back(piecePos - 17);
            if ((piecePos % 8) <= 6)
                tmpPiece->getPossibleMoves().push_back(piecePos - 15);
        }
    }
    if ((piecePos / 8) != 7) {
        if ((piecePos % 8) >= 2)
            tmpPiece->getPossibleMoves().push_back(piecePos + 6);
        if ((piecePos % 8) <= 5)
            tmpPiece->getPossibleMoves().push_back(piecePos + 10);
        if ((piecePos / 8) != 6) {
            if ((piecePos % 8) >= 1)
                tmpPiece->getPossibleMoves().push_back(piecePos + 15);
            if ((piecePos % 8) <= 6)
                tmpPiece->getPossibleMoves().push_back(piecePos + 17);
        }
    }

    tmpPiece->getDangerMoves().clear();

    for (int i = 0; i < tmpPiece->getPossibleMoves().size(); i++) {
        if (!playerTurn) {
            if ((tmpPiece->getPossibleMoves().at(i)) == blackPieces[3].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        } else {
            if ((tmpPiece->getPossibleMoves().at(i)) == whitePieces[4].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        }
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());
}

void ChessEngine::generatePawnMoves(Piece* tmpPiece) {
    tmpPiece->getPossibleMoves().clear();

    int piecePos{tmpPiece->getPosition()};

    if (tmpPiece->getPlayer()) {  // Если это белая пешка
        if ((piecePos / 8) != 0) {
            int i{0};
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - 8)) || (blackPieces[i].getPosition() == (piecePos - 8)))
                    break;
            }
            if ((i == 16) && playerTurn) {
                tmpPiece->getPossibleMoves().push_back(piecePos - 8);

                if (!tmpPiece->getMoved()) {
                    for (i = 0; i < 16; i++) {
                        if ((whitePieces[i].getPosition() == (piecePos - 16)) || (blackPieces[i].getPosition() == (piecePos - 16)))
                            break;
                    }
                    if (i == 16)
                        tmpPiece->getPossibleMoves().push_back(piecePos - 16);
                }
            }

            if ((piecePos % 8) != 0) {
                for (i = 0; i < 16; i++) {
                    if (!playerTurn || (blackPieces[i].getPosition() == (piecePos - 9)) || (whitePieces[i].getPosition() == (piecePos - 9))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    } else if ((blackPieces[i].getEnPassant() == (piecePos - 9)) && (blackPieces[i].getEnPassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    }
                }
            }

            if ((piecePos % 8) != 7) {
                for (i = 0; i < 16; i++) {
                    if (!playerTurn || (blackPieces[i].getPosition() == (piecePos - 7)) || (whitePieces[i].getPosition() == (piecePos - 7))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    } else if ((blackPieces[i].getEnPassant() == (piecePos - 7)) && (blackPieces[i].getEnPassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    }
                }
            }

        } else {  // НЕОБХОДИМО ПЕРЕДВИНУТЬ ПЕШКУ
            tmpPiece->setPiece('Q', tmpPiece->getPlayer(), tmpPiece->getPosition(), true);
            generateQueenMoves(tmpPiece);
            return;
        }

    } else {  // Если это чёрная пешка

        if ((piecePos / 8) != 7) {
            int i{0};
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + 8)) || (blackPieces[i].getPosition() == (piecePos + 8)))
                    break;
            }
            if ((i == 16) && !playerTurn) {
                tmpPiece->getPossibleMoves().push_back(piecePos + 8);

                if (!tmpPiece->getMoved()) {
                    for (i = 0; i < 16; i++) {
                        if ((whitePieces[i].getPosition() == (piecePos + 16)) || (blackPieces[i].getPosition() == (piecePos + 16)))
                            break;
                    }
                    if (i == 16)
                        tmpPiece->getPossibleMoves().push_back(piecePos + 16);
                }
            }

            if ((piecePos % 8) != 0) {
                for (i = 0; i < 16; i++) {
                    if (playerTurn || (whitePieces[i].getPosition() == (piecePos + 7)) || (blackPieces[i].getPosition() == (piecePos + 7))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    } else if ((whitePieces[i].getEnPassant() == (piecePos + 7)) && (whitePieces[i].getEnPassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    }
                }
            }

            if ((piecePos % 8) != 7) {
                for (i = 0; i < 16; i++) {
                    if (playerTurn || (whitePieces[i].getPosition() == (piecePos + 9)) || (blackPieces[i].getPosition() == (piecePos + 9))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    } else if ((whitePieces[i].getEnPassant() == (piecePos + 9)) && (whitePieces[i].getEnPassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    }
                }
            }

        } else {  // НЕОБХОДИМО ПЕРЕДВИНУТЬ ПЕШКУ
            tmpPiece->setPiece('Q', tmpPiece->getPlayer(), tmpPiece->getPosition(), true);
            generateQueenMoves(tmpPiece);
            return;
        }
    }

    tmpPiece->getDangerMoves().clear();

    for (int i = 0; i < tmpPiece->getPossibleMoves().size(); i++) {
        if (!playerTurn) {
            if ((tmpPiece->getPossibleMoves().at(i)) == blackPieces[3].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        } else {
            if ((tmpPiece->getPossibleMoves().at(i)) == whitePieces[4].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        }
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());
}

void ChessEngine::generateCastling(Piece* tmpPiece) {
    if (playerTurnCheck || (tmpPiece->getType() != 'K') || tmpPiece->getMoved() || (tmpPiece->getPlayer() != playerTurn))
        return;

    if (tmpPiece->getPlayer()) {  // Если это белый король
        // whitePieces[0] левая белая ладья, whitePieces[7] правая белая ладья
        if (!whitePieces[7].getMoved()) {
            int i{0};
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 61) || (whitePieces[i].getPosition() == 62)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 61) || (blackPieces[i].getPosition() == 62)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < blackPieces[i].getPossibleMoves().size(); j++) {
                        if ((blackPieces[i].getPossibleMoves().at(j) == 61) || (blackPieces[i].getPossibleMoves().at(j) == 62) ||
                            (blackPieces[i].getPossibleMoves().at(j) == 60)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17)
                        break;
                }
            }
            if (i != 17) {
                tmpPiece->getPossibleMoves().push_back(62);
            }
        }

        if (!whitePieces[0].getMoved()) {
            int i{0};
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 57) || (whitePieces[i].getPosition() == 58) || (whitePieces[i].getPosition() == 59)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 57) || (blackPieces[i].getPosition() == 58) || (blackPieces[i].getPosition() == 59)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < blackPieces[i].getPossibleMoves().size(); j++) {
                        if ((blackPieces[i].getPossibleMoves().at(j) == 58) || (blackPieces[i].getPossibleMoves().at(j) == 59) ||
                            (blackPieces[i].getPossibleMoves().at(j) == 60)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17)
                        break;
                }
            }
            if (i != 17) {
                tmpPiece->getPossibleMoves().push_back(58);
            }
        }
    } else {  // Если это чёрный король
        // blackPieces[7] левая чёрная ладья, blackPieces[0] правая чёрная ладья
        if (!blackPieces[7].getMoved()) {
            int i{0};
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 3) || (whitePieces[i].getPosition() == 2) || (whitePieces[i].getPosition() == 1)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 3) || (blackPieces[i].getPosition() == 2) || (blackPieces[i].getPosition() == 1)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < whitePieces[i].getPossibleMoves().size(); j++) {
                        if ((whitePieces[i].getPossibleMoves().at(j) == 3) || (whitePieces[i].getPossibleMoves().at(j) == 2) ||
                            (whitePieces[i].getPossibleMoves().at(j) == 4)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17)
                        break;
                }
            }
            if (i != 17) {
                tmpPiece->getPossibleMoves().push_back(2);
            }
        }

        if (!blackPieces[0].getMoved()) {
            int i{0};
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 5) || (whitePieces[i].getPosition() == 6)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 5) || (blackPieces[i].getPosition() == 6)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < whitePieces[i].getPossibleMoves().size(); j++) {
                        if ((whitePieces[i].getPossibleMoves().at(j) == 5) || (whitePieces[i].getPossibleMoves().at(j) == 6) ||
                            (whitePieces[i].getPossibleMoves().at(j) == 4)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17)
                        break;
                }
            }
            if (i != 17) {
                tmpPiece->getPossibleMoves().push_back(6);
            }
        }
    }
}

void ChessEngine::checkMate() {
    // Не более двух фигур в теории могут нападать на короля одновременно
    // Шах от одной фигуры может быть остановлен отходом короля на
    // клетку которая не атакована, или ходом другой фигуры, которая перекрывает атакуЮ либо съедает атакующую фигуру
    // Двойной шах может быть остановлен только отходом короля

    Piece* check1{NULL};
    Piece* check2{NULL};

    // Проверка нахождения под шахом короля ходящего игрока
    // whitePieces[4] это белый король, blackPieces[3] это чёрный король
    for (int i = 0; i < 16; i++) {
        if (playerTurn) {  // Если ход белых
            for (int j = 0; j < blackPieces[i].getPossibleMoves().size(); j++) {
                if (whitePieces[4].getPosition() == blackPieces[i].getPossibleMoves().at(j)) {
                    if (check1 == NULL) {
                        playerTurnCheck = true;
                        check1 = &blackPieces[i];
                        break;
                    } else if (check2 == NULL) {
                        // playerTurnCheck = true;
                        check2 = &blackPieces[i];
                        break;
                    }
                }
            }
        } else {  // Если ход чёрных
            for (int j = 0; j < whitePieces[i].getPossibleMoves().size(); j++) {
                if (blackPieces[3].getPosition() == whitePieces[i].getPossibleMoves().at(j)) {
                    if (check1 == NULL) {
                        playerTurnCheck = true;
                        check1 = &whitePieces[i];
                        break;
                    } else if (check2 == NULL) {
                        // playerTurnCheck = true;
                        check2 = &whitePieces[i];
                        break;
                    }
                }
            }
        }

        if (check2 != NULL)
            break;
    }

    // Проверка на наличие у игрока фигур способных остановить шах
    // Если не находится никаких ходов выводящих короля из под шаха -> мат
    if (playerTurnCheck) {
        if (check2 != NULL) {  // Если шах поставлен двумя фигурами одновременно, оставляем только ходы королём, поскольку остальные не смогут остановить два шаха сразу
            if (playerTurn)
                for (int i = 0; i < 16; i++)
                    if (whitePieces[i].getType() != 'K')
                        whitePieces[i].getPossibleMoves().clear();
                    else
                        for (int i = 0; i < 16; i++)
                            if (blackPieces[i].getType() != 'K')
                                blackPieces[i].getPossibleMoves().clear();
        } else {  // Если шах поставлен 1 фигурой

            for (int j = 0; j < 16; j++) {  // Обход по элементам массива фигур
                std::vector<int> tmpMoves;

                if (playerTurn) {  // Если ходят белые
                    if (whitePieces[j].getType() == 'K')
                        continue;
                    for (int o = 0; o < whitePieces[j].getPossibleMoves().size(); o++) {
                        if (whitePieces[j].getPossibleMoves().empty())
                            break;
                        for (int i = 0; i < check1->getDangerMoves().size(); i++) {  // Checking piece moves counter
                            if ((whitePieces[j].getPossibleMoves().at(o) == check1->getDangerMoves().at(i))) {
                                tmpMoves.push_back(whitePieces[j].getPossibleMoves().at(o));
                                break;
                            }
                        }
                    }

                    whitePieces[j].getPossibleMoves().clear();
                    whitePieces[j].getPossibleMoves() = tmpMoves;
                } else {  // Если ходят чёрные
                    if (blackPieces[j].getType() == 'K')
                        continue;
                    for (int o = 0; o < blackPieces[j].getPossibleMoves().size(); o++) {
                        if (blackPieces[j].getPossibleMoves().empty())
                            break;
                        for (int i = 0; i < check1->getDangerMoves().size(); i++) {  // Checking piece moves counter
                            if ((blackPieces[j].getPossibleMoves().at(o) == check1->getDangerMoves().at(i))) {
                                tmpMoves.push_back(blackPieces[j].getPossibleMoves().at(o));
                                break;
                            }
                        }
                    }
                    blackPieces[j].getPossibleMoves().clear();
                    blackPieces[j].getPossibleMoves() = tmpMoves;
                }
            }
        }

        // Bug fix
        //  whitePieces[4] is white King , blackPieces[3] is black King
        Piece* curKing;
        if (playerTurn) {
            curKing = &whitePieces[4];
        } else {
            curKing = &blackPieces[3];
        }
        if (check1 != NULL) {
            if ((check1->getType() == 'Q') || (check1->getType() == 'R' || (check1->getType() == 'B'))) {
                int checkPos{check1->getPosition()};

                if ((check1->getType() == 'Q') || (check1->getType() == 'R')) {
                    for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                        if (curKing->getPossibleMoves().at(i) != checkPos) {
                            if ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            else if ((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                    if (curKing->getPossibleMoves().at(i) != checkPos) {
                        if ((curKing->getPosition() % 8) < (checkPos % 8)) {      // King left of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) {  // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            } else if ((checkPos / 8) < (curKing->getPosition() / 8)) {  // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        } else if ((checkPos % 8) < (curKing->getPosition() % 8)) {  // King right of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) {     // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            } else if ((checkPos / 8) < (curKing->getPosition() / 8)) {  // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }
        // Bug fix
        if (check2 != NULL) {
            if ((check2->getType() == 'Q') || (check2->getType() == 'R' || (check2->getType() == 'B'))) {
                int checkPos{check2->getPosition()};

                if ((check2->getType() == 'Q') || (check2->getType() == 'R')) {
                    for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                        if (curKing->getPossibleMoves().at(i) != checkPos) {
                            if ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            else if ((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                    if (curKing->getPossibleMoves().at(i) != checkPos) {
                        if ((curKing->getPosition() % 8) < (checkPos % 8)) {      // King left of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) {  // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            } else if ((checkPos / 8) < (curKing->getPosition() / 8)) {  // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        } else if ((checkPos % 8) < (curKing->getPosition() % 8)) {  // King right of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) {     // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            } else if ((checkPos / 8) < (curKing->getPosition() / 8)) {  // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) &&
                                    ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }

    } else {
        generateCastling(&whitePieces[4]);
        generateCastling(&blackPieces[3]);
    }

    // Проверяем, имеет ли игрок, чей ход наступил, доступные ходы
    int i{0};
    for (i = 0; i < 16; i++) {
        if (playerTurn) {
            if (!whitePieces[i].getPossibleMoves().empty())
                break;
        } else {
            if (!blackPieces[i].getPossibleMoves().empty())
                break;
        }
    }
    if (i == 16) {
        mate = true;
    }
}
