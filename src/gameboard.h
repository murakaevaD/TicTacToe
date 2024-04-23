#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

class GameBoard {
public:
    explicit GameBoard(int size = 3);
    void reset();
    bool makeMove(int row, int col, char player);
    char getCurrentPlayer() const;
    char checkWinner() const;

private:
    int size;
    std::vector<std::vector<char>> board;
    char currentPlayer;
    bool checkRows() const;
    bool checkCols() const;
    bool checkDiagonals() const;
};

#endif // GAMEBOARD_H
