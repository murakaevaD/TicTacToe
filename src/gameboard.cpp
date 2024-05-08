#include "gameboard.h"
#include <algorithm>

GameBoard::GameBoard(int initialSize)
    : current(Player::X), minRow(0), maxRow(initialSize - 1), minCol(0), maxCol(initialSize - 1) {
    board.resize(initialSize, std::vector<Player>(initialSize, Player::None));
}

Player GameBoard::currentPlayer() const {
    return current;
}

void GameBoard::makeMove(int row, int col) {
    if (row < minRow || row > maxRow || col < minCol || col > maxCol) {
        expandBoard(row, col);
    }

    board[row - minRow][col - minCol] = current;
    current = (current == Player::X) ? Player::O : Player::X;
}

void GameBoard::expandBoard(int row, int col) {
    if (row <= minRow) expandUp();
    if (row >= maxRow) expandDown();
    if (col <= minCol) expandLeft();
    if (col >= maxCol) expandRight();
}

void GameBoard::expandUp() {
    board.insert(board.begin(), std::vector<Player>(maxCol - minCol + 1, Player::None));
    minRow--;
}

void GameBoard::expandDown() {
    board.push_back(std::vector<Player>(maxCol - minCol + 1, Player::None));
    maxRow++;
}

void GameBoard::expandLeft() {
    for (auto& row : board) {
        row.insert(row.begin(), Player::None);
    }
    minCol--;
}

void GameBoard::expandRight() {
    for (auto& row : board) {
        row.push_back(Player::None);
    }
    maxCol++;
}

int GameBoard::size() const {
    return maxRow - minRow + 1;
}

Player GameBoard::getPlayerAt(int row, int col) const {
    if (row < minRow || row > maxRow || col < minCol || col > maxCol) {
        return Player::None;
    }
    return board[row - minRow][col - minCol];
}

bool GameBoard::isWin(Player player) const {
    int totalRows = maxRow - minRow + 1;
    int totalCols = maxCol - minCol + 1;

    for (int i = 0; i < totalRows; ++i) {
        if (std::all_of(board[i].begin(), board[i].end(), [player](Player p) { return p == player; })) {
            return true;
        }
    }
    for (int j = 0; j < totalCols; ++j) {
        bool columnWin = true;
        for (int i = 0; i < totalRows; ++i) {
            if (board[i][j] != player) {
                columnWin = false;
                break;
            }
        }
        if (columnWin) return true;
    }

    bool diag1 = true;
    for (int i = 0; i < std::min(totalRows, totalCols); ++i) {
        if (board[i][i] != player) {
            diag1 = false;
            break;
        }
    }

    bool diag2 = true;
    for (int i = 0; i < std::min(totalRows, totalCols); ++i) {
        if (board[i][totalCols - i - 1] != player) {
            diag2 = false;
            break;
        }
    }

    return diag1 || diag2;
}


bool GameBoard::checkWin() const {
    return isWin(current == Player::X ? Player::O : Player::X);
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
