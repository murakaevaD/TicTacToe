#include <gtest/gtest.h>
#include "GameBoard.h"

class GameBoardTest : public ::testing::Test {
protected:
    GameBoard board;

    void SetUp() override {
        board = GameBoard(3);
    }
};

TEST_F(GameBoardTest, HorizontalWin) {
    board.makeMove(0, 0);  // X
    board.makeMove(1, 0);  // O
    board.makeMove(0, 1);  // X
    board.makeMove(1, 1);  // O
    board.makeMove(0, 2);  // X

    ASSERT_TRUE(board.isWin(Player::X));
    ASSERT_FALSE(board.isWin(Player::O));
}

TEST_F(GameBoardTest, VerticalWin) {
    board.makeMove(0, 0);  // X
    board.makeMove(0, 1);  // O
    board.makeMove(1, 0);  // X
    board.makeMove(1, 1);  // O
    board.makeMove(2, 0);  // X

    ASSERT_TRUE(board.isWin(Player::X));
    ASSERT_FALSE(board.isWin(Player::O));
}

TEST_F(GameBoardTest, DiagonalWin) {
    board.makeMove(0, 0);  // X
    board.makeMove(1, 0);  // O
    board.makeMove(1, 1);  // X
    board.makeMove(2, 1);  // O
    board.makeMove(2, 2);  // X

    ASSERT_TRUE(board.isWin(Player::X));
    ASSERT_FALSE(board.isWin(Player::O));
}

TEST_F(GameBoardTest, SecondaryDiagonalWin) {
    board.makeMove(0, 2);  // X
    board.makeMove(0, 1);  // O
    board.makeMove(1, 1);  // X
    board.makeMove(0, 0);  // O
    board.makeMove(2, 0);  // X

    ASSERT_TRUE(board.isWin(Player::X));
    ASSERT_FALSE(board.isWin(Player::O));
}

TEST_F(GameBoardTest, DrawTest1) {
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(0, 2); // X
    board.makeMove(1, 0); // O
    board.makeMove(1, 1); // X
    board.makeMove(1, 2); // O
    board.makeMove(2, 0); // X
    board.makeMove(2, 1); // O
    board.makeMove(2, 2); // X

    ASSERT_TRUE(board.isBoardFull());
}

TEST_F(GameBoardTest, DrawTest2) {
    board.makeMove(0, 0); // O
    board.makeMove(0, 1); // X
    board.makeMove(0, 2); // O
    board.makeMove(1, 0); // X
    board.makeMove(1, 1); // O
    board.makeMove(1, 2); // X
    board.makeMove(2, 0); // O
    board.makeMove(2, 1); // X
    board.makeMove(2, 2); // O

    ASSERT_TRUE(board.isBoardFull());
}

TEST_F(GameBoardTest, DrawTest3) {
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // X
    board.makeMove(0, 2); // O
    board.makeMove(1, 0); // O
    board.makeMove(1, 1); // O
    board.makeMove(1, 2); // X
    board.makeMove(2, 0); // X
    board.makeMove(2, 1); // O
    board.makeMove(2, 2); // X

    ASSERT_TRUE(board.isBoardFull());
}

TEST_F(GameBoardTest, DrawTest4) {
    board.makeMove(0, 0); // O
    board.makeMove(0, 1); // O
    board.makeMove(0, 2); // X
    board.makeMove(1, 0); // X
    board.makeMove(1, 1); // X
    board.makeMove(1, 2); // O
    board.makeMove(2, 0); // O
    board.makeMove(2, 1); // X
    board.makeMove(2, 2); // O

    ASSERT_TRUE(board.isBoardFull());
}

TEST_F(GameBoardTest, DrawTest5) {
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(0, 2); // X
    board.makeMove(1, 0); // X
    board.makeMove(1, 1); // O
    board.makeMove(1, 2); // O
    board.makeMove(2, 0); // O
    board.makeMove(2, 1); // X
    board.makeMove(2, 2); // X
    ASSERT_TRUE(board.isBoardFull());
}

