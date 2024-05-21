#include "gameboard.h"
#include <cstdlib>

GameBoard::GameBoard(int size) : boardSizeX(size), boardSizeY(size), current(Player::X), expandingMode(false) {
    board.resize(boardSizeX, std::vector<Player>(boardSizeY, Player::None));
}

void GameBoard::makeMove(int row, int col) {
    if (row >= 0 && row < boardSizeY && col >= 0 && col < boardSizeX && board[row][col] == Player::None) {
        board[row][col] = current;
        if (expandingMode) {
            expandBoard(row, col);
        }
        current = (current == Player::X) ? Player::O : Player::X;
    }
}

bool GameBoard::isWin(Player player, int winCondition) const {
    for (int i = 0; i < boardSizeY; ++i) {
        int rowWinCount = 0;
        for (int j = 0; j < boardSizeX; ++j) {
            if (board[i][j] == player) {
                rowWinCount++;
                if (rowWinCount == winCondition) return true;
            } else {
                rowWinCount = 0;
            }
        }
    }

    for (int j = 0; j < boardSizeX; ++j) {
        int colWinCount = 0;
        for (int i = 0; i < boardSizeY; ++i) {
            if (board[i][j] == player) {
                colWinCount++;
                if (colWinCount == winCondition) return true;
            } else {
                colWinCount = 0;
            }
        }
    }

    for (int i = 0; i <= boardSizeY - winCondition; ++i) {
        for (int j = 0; j <= boardSizeX - winCondition; ++j) {
            bool diagWin = true;
            for (int k = 0; k < winCondition; ++k) {
                if (board[i + k][j + k] != player) {
                    diagWin = false;
                    break;
                }
            }
            if (diagWin) return true;
        }
    }

    for (int i = 0; i <= boardSizeY - winCondition; ++i) {
        for (int j = winCondition - 1; j < boardSizeX; ++j) {
            bool diagWin = true;
            for (int k = 0; k < winCondition; ++k) {
                if (board[i + k][j - k] != player) {
                    diagWin = false;
                    break;
                }
            }
            if (diagWin) return true;
        }
    }

    return false;
}


bool GameBoard::checkWin(int winCondition) const {
    return isWin(Player::X, winCondition) || isWin(Player::O, winCondition);
}

bool GameBoard::isBoardFull() const {
    for (const auto& row : board) {
        for (auto cell : row) {
            if (cell == Player::None) return false;
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

int GameBoard::sizeY() const {
    return boardSizeY;
}

int GameBoard::sizeX() const {
    return boardSizeX;
}

Player GameBoard::getPlayerAt(int row, int col) const {
    return (row >= 0 && row < sizeY() && col >= 0 && col < sizeX()) ? board[row][col] : Player::None;
}

void GameBoard::makeRandomMove() {
    std::vector<std::pair<int, int>> freeCells;

    for (int row = 0; row < boardSizeX; ++row) {
        for (int col = 0; col < boardSizeX; ++col) {
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

void GameBoard::expandBoard(int row, int col) {
    const int maxSize = 18;
    bool expanded = false;

    if (row == 0 && boardSizeY + 3 <= maxSize) { // Expand upwards
        for (int i = 0; i < 3; ++i) {
            board.insert(board.begin(), std::vector<Player>(boardSizeX, Player::None));
        }
        boardSizeY += 3;
        expanded = true;
    }

    if (row == boardSizeY - 1 && boardSizeY + 3 <= maxSize) { // Expand downwards
        for (int i = 0; i < 3; ++i) {
            board.push_back(std::vector<Player>(boardSizeX, Player::None));
        }
        boardSizeY += 3;
        expanded = true;
    }

    if (col == 0 && boardSizeX + 3 <= maxSize) { // Expand leftwards
        for (auto& r : board) {
            for (int i = 0; i < 3; ++i) {
                r.insert(r.begin(), Player::None);
            }
        }
        boardSizeX += 3;
        expanded = true;
    }

    if (col == boardSizeX - 1 && boardSizeX + 3 <= maxSize) { // Expand rightwards
        for (auto& r : board) {
            for (int i = 0; i < 3; ++i) {
                r.push_back(Player::None);
            }
        }
        boardSizeX += 3;
        expanded = true;
    }

    if (expanded) {
        if (boardSizeX > maxSize) {
            boardSizeX = maxSize;
        }
        if (boardSizeY > maxSize) {
            boardSizeY = maxSize;
        }
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

void GameBoard::setExpandingMode(bool enabled) {
    expandingMode = enabled;
}
