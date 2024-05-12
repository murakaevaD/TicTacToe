#include "gameboard.h"
#include <cstdlib>

GameBoard::GameBoard(int size) : boardSize(size), current(Player::X), expandingMode(false) {
    board.resize(boardSize, std::vector<Player>(boardSize, Player::None));
}

void GameBoard::makeMove(int row, int col) {
    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize && board[row][col] == Player::None) {
        board[row][col] = current;
        if (expandingMode) {
            expandBoard(row, col);
        }
        current = (current == Player::X) ? Player::O : Player::X;
    }
}

bool GameBoard::isWin(Player player, int winCondition) const {
    // Проверяем горизонтальные и вертикальные линии
    for (int i = 0; i < boardSize; ++i) {
        int rowWinCount = 0, colWinCount = 0;
        for (int j = 0; j < boardSize; ++j) {
            // Горизонтальные линии
            if (board[i][j] == player) {
                rowWinCount++;
                if (rowWinCount == winCondition) return true;
            } else {
                rowWinCount = 0;
            }
            // Вертикальные линии
            if (board[j][i] == player) {
                colWinCount++;
                if (colWinCount == winCondition) return true;
            } else {
                colWinCount = 0;
            }
        }
    }

    // Проверяем главную диагональ
    for (int i = 0; i <= boardSize - winCondition; ++i) {
        for (int j = 0; j <= boardSize - winCondition; ++j) {
            bool diagWin = true;
            for (int k = 0; k < winCondition; ++k) {
                if (board[i+k][j+k] != player) {
                    diagWin = false;
                    break;
                }
            }
            if (diagWin) return true;
        }
    }

    // Проверяем побочную диагональ
    for (int i = 0; i <= boardSize - winCondition; ++i) {
        for (int j = winCondition - 1; j < boardSize; ++j) {
            bool diagWin = true;
            for (int k = 0; k < winCondition; ++k) {
                if (board[i+k][j-k] != player) {
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

int GameBoard::size() const {
    return boardSize;
}

Player GameBoard::getPlayerAt(int row, int col) const {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize) ? board[row][col] : Player::None;
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

void GameBoard::expandBoard(int row, int col) {
    const int maxSize = 15;
    if (boardSize >= maxSize) return;

    bool expanded = false;
    if (row == 0 && col == 0) {
        board.insert(board.begin(), std::vector<Player>(boardSize, Player::None));
        for (auto& r : board) {
            r.insert(r.begin(), Player::None);
        }
        expanded = true;
    }
    if (row == 0 && col == boardSize - 1) {
        board.insert(board.begin(), std::vector<Player>(boardSize, Player::None));
        for (auto& r : board) {
            r.push_back(Player::None);
        }
        expanded = true;
    }

    if (row == boardSize - 1 && col == 0) {
        board.push_back(std::vector<Player>(boardSize, Player::None));
        for (auto& r : board) {
            r.insert(r.begin(), Player::None);
        }
        expanded = true;
    }

    if (row == boardSize - 1 && col == boardSize - 1) {
        board.push_back(std::vector<Player>(boardSize, Player::None));
        for (auto& r : board) {
            r.push_back(Player::None);
        }
        expanded = true;
    }

    if (expanded) {
        boardSize++;
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
