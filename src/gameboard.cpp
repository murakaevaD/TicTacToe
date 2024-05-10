#include "gameboard.h"
#include <cstdlib>

GameBoard::GameBoard(int size) : boardSize(size), current(Player::X) {
    board.resize(boardSize, std::vector<Player>(boardSize, Player::None));
}

void GameBoard::makeMove(int row, int col) {
    if (board[row][col] == Player::None) {
        board[row][col] = current;
        current = (current == Player::X) ? Player::O : Player::X;
    }
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

void GameBoard::setCurrentPlayer(Player player) {
    current = player;
}

Player GameBoard::currentPlayer() const {
    return current;
}

int GameBoard::size() const {
    return boardSize;
}

Player GameBoard::getPlayerAt(int row, int col) const {
    return board[row][col];
}

void GameBoard::makeRandomMove() {
    std::vector<std::pair<int, int>> freeCells;

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board[row][col] == Player::None) {
                freeCells.emplace_back(row, col);
            }
        }
    }

    if (!freeCells.empty()) {
        int index = rand() % freeCells.size();
        int row = freeCells[index].first;
        int col = freeCells[index].second;
        board[row][col] = current;
        current = (current == Player::X) ? Player::O : Player::X;
    }
}


void GameBoard::reset() {
    for (auto& row : board) {
        std::fill(row.begin(), row.end(), Player::None);
    }
    current = Player::X;
}

void GameBoard::clearBoard() {
    for (auto& row : board) {
        std::fill(row.begin(), row.end(), Player::None);
    }
}

