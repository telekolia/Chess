#include <iostream>
#include <vector>
#include <utility>

#include "../ChessPiece/СhessPieceTest.hpp"

const int SIZE = 8;

bool IsWhitePiece(int pieceCode) {
    return (pieceCode / 10) == 0;
}

bool IfPiece(int pieceCode, PieceType type, bool isWhite) {
    return IsWhitePiece(pieceCode) == isWhite && pieceCode % 10 == static_cast<int>(type);
}

// Функция для проверки, находится ли клетка (x, y) под атакой белых фигур
bool isUnderAttack(int board[SIZE][SIZE], int x, int y, bool isWhite) {
    // Проверка атаки пешками
    if (y < 7) {
        if (isWhite) {
            if (x >= 2 && x <= 7) {
                if (IfPiece(board[x][y], PieceType::Pawn, !isWhite) || IfPiece(board[x-1][y+1], PieceType::Pawn, !isWhite)) {
                    return true;
                }
            }
            if (IfPiece(board[x][y], PieceType::Pawn, !isWhite) || IfPiece(board[x-1][y+1], PieceType::Pawn, !isWhite)) {
            return true;
            }
            if (y < SIZE-1 && board[x-1][y+1] == 1) {
                return true;
            }
        }
    }

    // Проверка атаки ладьями и королевами
    for (int i = x+1; i < SIZE; ++i) {
        if (board[i][y] != 0) {
            if (board[i][y] == 2 || board[i][y] == 5) return true;
            break;
        }
    }
    for (int i = x-1; i >= 0; --i) {
        if (board[i][y] != 0) {
            if (board[i][y] == 2 || board[i][y] == 5) return true;
            break;
        }
    }
    for (int j = y+1; j < SIZE; ++j) {
        if (board[x][j] != 0) {
            if (board[x][j] == 2 || board[x][j] == 5) return true;
            break;
        }
    }
    for (int j = y-1; j >= 0; --j) {
        if (board[x][j] != 0) {
            if (board[x][j] == 2 || board[x][j] == 5) return true;
            break;
        }
    }

    // Проверка атаки слонами и королевами
    for (int i = 1; x+i < SIZE && y+i < SIZE; ++i) {
        if (board[x+i][y+i] != 0) {
            if (board[x+i][y+i] == 4 || board[x+i][y+i] == 5) return true;
            break;
        }
    }
    for (int i = 1; x+i < SIZE && y-i >= 0; ++i) {
        if (board[x+i][y-i] != 0) {
            if (board[x+i][y-i] == 4 || board[x+i][y-i] == 5) return true;
            break;
        }
    }
    for (int i = 1; x-i >= 0 && y+i < SIZE; ++i) {
        if (board[x-i][y+i] != 0) {
            if (board[x-i][y+i] == 4 || board[x-i][y+i] == 5) return true;
            break;
        }
    }
    for (int i = 1; x-i >= 0 && y-i >= 0; ++i) {
        if (board[x-i][y-i] != 0) {
            if (board[x-i][y-i] == 4 || board[x-i][y-i] == 5) return true;
            break;
        }
    }

    // Проверка атаки конями
    const int knightMoves[8][2] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}};
    for (auto move : knightMoves) {
        int nx = x + move[0];
        int ny = y + move[1];
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == 3) {
            return true;
        }
    }

    // Проверка атаки королем (для выявления смежных королей)
    for (int i = max(0, x-1); i <= min(SIZE-1, x+1); ++i) {
        for (int j = max(0, y-1); j <= min(SIZE-1, y+1); ++j) {
            if (board[i][j] == 6) return true;
        }
    }

    return false;
}

// Функция для проверки, есть ли хотя бы один возможный ход для черного короля
bool hasLegalMove(int board[SIZE][SIZE], int kingX, int kingY) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = kingX + dx;
            int ny = kingY + dy;

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                // Клетка должна быть либо пустой, либо содержать белую фигуру
                if (board[nx][ny] == 0 || (board[nx][ny] >= 1 && board[nx][ny] <= 6)) {
                    // Сохраняем исходное состояние
                    int original = board[nx][ny];
                    board[kingX][kingY] = 0;
                    board[nx][ny] = 16;

                    bool underAttack = isUnderAttack(board, nx, ny);

                    // Восстанавливаем исходное состояние
                    board[kingX][kingY] = 16;
                    board[nx][ny] = original;

                    if (!underAttack) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int board[SIZE][SIZE];

    // Ввод доски
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> board[i][j];
        }
    }

    // Находим позицию черного короля
    int kingX = -1, kingY = -1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 16) {
                kingX = i;
                kingY = j;
                break;
            }
        }
        if (kingX != -1) break;
    }

    if (kingX == -1) {
        cout << "Черный король не найден на доске!" << endl;
        return 1;
    }

    // Проверяем, находится ли король под шахом
    bool check = isUnderAttack(board, kingX, kingY);

    if (!check) {
        cout << "Ничья - король не под шахом" << endl;
        return 0;
    }

    // Проверяем, есть ли возможные ходы
    bool canMove = hasLegalMove(board, kingX, kingY);

    if (canMove) {
        cout << "Шах - король под атакой, но есть возможные ходы" << endl;
    } else {
        cout << "Мат - король под атакой и нет возможных ходов" << endl;
    }

    return 0;
}
