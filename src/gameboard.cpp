#include "gameboard.h"

GameBoard::GameBoard(int size) : boardSize(size), current(Player::X) {
    board.resize(boardSize, std::vector<Player>(boardSize, Player::None));
}

Player GameBoard::currentPlayer() const {
    return current;
}

void GameBoard::makeMove(int row, int col) {
    if (board[row][col] == Player::None) {
        board[row][col] = current;
        current = (current == Player::X) ? Player::O : Player::X;
    }
}

int GameBoard::size() const {
    return boardSize;
}

Player GameBoard::getPlayerAt(int row, int col) const {
    return board[row][col];
}

bool GameBoard::isWin(Player player) const {
    for (int row = 0; row < boardSize; ++row) {
        bool rowWin = true;
        for (int col = 0; col < boardSize; ++col) {
            if (board[row][col] != player) {
                rowWin = false;
                break;
            }
        }
        if (rowWin) return true;
    }

    for (int col = 0; col < boardSize; ++col) {
        bool colWin = true;
        for (int row = 0; row < boardSize; ++row) {
            if (board[row][col] != player) {
                colWin = false;
                break;
            }
        }
        if (colWin) return true;
    }

    bool mainDiagWin = true;
    for (int i = 0; i < boardSize; ++i) {
        if (board[i][i] != player) {
            mainDiagWin = false;
            break;
        }
    }
    if (mainDiagWin) return true;

    bool secDiagWin = true;
    for (int i = 0; i < boardSize; ++i) {
        if (board[i][boardSize - i - 1] != player) {
            secDiagWin = false;
            break;
        }
    }
    if (secDiagWin) return true;

    return false;
}

bool GameBoard::checkWin() const {
    return isWin(Player::X) || isWin(Player::O);
}

bool GameBoard::isBoardFull() const {
    for (const auto& row : board) {
        for (auto cell : row) {
            if (cell == Player::None) {
                return false;
            }
        }
    }
    return true;
}
