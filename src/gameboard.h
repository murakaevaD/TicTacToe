#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

enum class Player { None, X, O };

class GameBoard {
public:
    GameBoard(int size = 3);

    void makeMove(int row, int col);
    bool isWin(Player player, int winCondition) const;
    bool checkWin(int winCondition) const;
    bool isBoardFull() const;
    void setCurrentPlayer(Player player);
    Player currentPlayer() const;
    int size() const;
    Player getPlayerAt(int row, int col) const;
    void makeRandomMove();
    void expandBoard(int row, int col);
    void reset();
    void clearBoard();
    void setExpandingMode(bool enabled);

private:
    std::vector<std::vector<Player>> board;
    int boardSize;
    Player current;
    bool expandingMode;

    friend class TestGameBoard;
};

#endif // GAMEBOARD_H
