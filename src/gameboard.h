#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

enum class Player { None, X, O };

class GameBoard {
public:
    GameBoard(int size = 3);
    Player currentPlayer() const;
    void makeMove(int row, int col);
    bool checkWin() const;
    int size() const;
    Player getPlayerAt(int row, int col) const;
    bool isWin(Player player) const;
    bool isBoardFull() const;

private:
    std::vector<std::vector<Player>> board;
    Player current;
    int boardSize;
};

#endif
