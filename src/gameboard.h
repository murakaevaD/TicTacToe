#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <QString>

class Player {
public:
    explicit Player(QString symbol) : symbol(symbol) {}

    QString getSymbol() const { return symbol; }

private:
    QString symbol;
};

class GameBoard {
public:
    explicit GameBoard(int size = 3);
    void reset();
    bool makeMove(int row, int col, Player* player);
    Player* getCurrentPlayer() const;
    Player* checkWinner() const;
    void switchPlayers();

private:
    int size;
    std::vector<std::vector<Player*>> board;
    Player player1, player2;
    Player* currentPlayer;

    bool checkRows() const;
    bool checkCols() const;
    bool checkDiagonals() const;
};

#endif // GAMEBOARD_H
