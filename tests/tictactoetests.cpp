#include "tictactoetests.h"
#include <gameboard.h>

void TestGameBoard::testHorizontalWin() {
    GameBoard board(3);

    // Победа в первой строке
    board.makeMove(0, 0); // X
    board.makeMove(1, 0); // O
    board.makeMove(0, 1); // X
    board.makeMove(1, 1); // O
    board.makeMove(0, 2); // X
    QVERIFY(board.checkWin());

    // Победа во второй строке
    GameBoard board2(3);
    board2.makeMove(1, 0); // X
    board2.makeMove(0, 0); // O
    board2.makeMove(1, 1); // X
    board2.makeMove(0, 1); // O
    board2.makeMove(1, 2); // X
    QVERIFY(board2.checkWin());

    // Победа в третьей строке
    GameBoard board3(3);
    board3.makeMove(2, 0); // X
    board3.makeMove(0, 0); // O
    board3.makeMove(2, 1); // X
    board3.makeMove(0, 1); // O
    board3.makeMove(2, 2); // X
    QVERIFY(board3.checkWin());
}


void TestGameBoard::testVerticalWin() {
    GameBoard board(3);

    // Победа в первом столбце
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(1, 0); // X
    board.makeMove(1, 1); // O
    board.makeMove(2, 0); // X
    QVERIFY(board.checkWin());

    // Победа во втором столбце
    GameBoard board2(3);
    board2.makeMove(0, 1); // X
    board2.makeMove(0, 0); // O
    board2.makeMove(1, 1); // X
    board2.makeMove(1, 0); // O
    board2.makeMove(2, 1); // X
    QVERIFY(board2.checkWin());

    // Победа в третьем столбце
    GameBoard board3(3);
    board3.makeMove(0, 2); // X
    board3.makeMove(0, 0); // O
    board3.makeMove(1, 2); // X
    board3.makeMove(1, 0); // O
    board3.makeMove(2, 2); // X
    QVERIFY(board3.checkWin());
}

void TestGameBoard::testDiagonalWin() {
    GameBoard board(3);

    // Победа по главной диагонали
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(1, 1); // X
    board.makeMove(1, 0); // O
    board.makeMove(2, 2); // X
    QVERIFY(board.checkWin());

    // Победа по побочной диагонали
    GameBoard board2(3);
    board2.makeMove(0, 2); // X
    board2.makeMove(0, 1); // O
    board2.makeMove(1, 1); // X
    board2.makeMove(1, 0); // O
    board2.makeMove(2, 0); // X
    QVERIFY(board2.checkWin());
}

void TestGameBoard::testDraw1() {
    GameBoard board(3);
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(0, 2); // X
    board.makeMove(1, 1); // O
    board.makeMove(1, 0); // X
    board.makeMove(2, 0); // O
    board.makeMove(1, 2); // X
    board.makeMove(2, 1); // O
    board.makeMove(2, 2); // X
    QVERIFY(board.isBoardFull());
}

void TestGameBoard::testDraw2() {
    GameBoard board(3);
    board.makeMove(0, 0); // X
    board.makeMove(0, 2); // O
    board.makeMove(2, 0); // X
    board.makeMove(2, 2); // O
    board.makeMove(1, 1); // X
    board.makeMove(0, 1); // O
    board.makeMove(1, 0); // X
    board.makeMove(1, 2); // O
    board.makeMove(2, 1); // X
    QVERIFY(board.isBoardFull());
}

void TestGameBoard::testDraw3() {
    GameBoard board(3);
    board.makeMove(1, 1); // X
    board.makeMove(0, 0); // O
    board.makeMove(0, 2); // X
    board.makeMove(2, 0); // O
    board.makeMove(2, 2); // X
    board.makeMove(0, 1); // O
    board.makeMove(2, 1); // X
    board.makeMove(1, 0); // O
    board.makeMove(1, 2); // X
    QVERIFY(board.isBoardFull());
}

void TestGameBoard::testDraw4() {
    GameBoard board(3);
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(0, 2); // X
    board.makeMove(1, 2); // O
    board.makeMove(2, 2); // X
    board.makeMove(2, 1); // O
    board.makeMove(2, 0); // X
    board.makeMove(1, 0); // O
    board.makeMove(1, 1); // X
    QVERIFY( board.isBoardFull());
}

void TestGameBoard::testDraw5() {
    GameBoard board(3);
    board.makeMove(0, 0); // X
    board.makeMove(0, 2); // O
    board.makeMove(0, 1); // X
    board.makeMove(1, 0); // O
    board.makeMove(1, 2); // X
    board.makeMove(2, 0); // O
    board.makeMove(2, 2); // X
    board.makeMove(2, 1); // O
    board.makeMove(1, 1); // X
    QVERIFY(board.isBoardFull());
}

QTEST_MAIN(TestGameBoard)
