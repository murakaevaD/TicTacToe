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

bool GameBoard::checkWin() const {
    return isWin(Player::X) || isWin(Player::O);
}

int GameBoard::size() const {
    return boardSize;
}

Player GameBoard::getPlayerAt(int row, int col) const {
    return board[row][col];
}

bool GameBoard::isWin(Player player) const {
    // Проверка победы по строкам, столбцам и диагоналям
    return false;
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
