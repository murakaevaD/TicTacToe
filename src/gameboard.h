#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

enum class Player { None, X, O };

class GameBoard {
public:
    explicit GameBoard(int size = 3);
    Player currentPlayer() const;
    Player getPlayerAt(int row, int col) const;
    void makeMove(int row, int col);
    void makeRandomMove();
    void setSize(int newSize);
    void setCurrentPlayer(Player player);
    void reset();
    bool checkWin() const;
    void extracted(Player &player, int &row, bool &rowWin) const;
    bool isWin(Player player) const;
    bool isBoardFull() const;
    int size() const;

private:
    std::vector<std::vector<Player>> board;
    Player current;
    int boardSize;
    void clearBoard();
};

#endif // GAMEBOARD_H
