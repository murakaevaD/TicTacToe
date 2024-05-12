#ifndef TESTGAMEBOARD_H
#define TESTGAMEBOARD_H

#include <QtTest/QtTest>
#include <QPointer>
#include "gameboard.h"

class TestGameBoard : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void testHorizontalWin();
    void testVerticalWin();
    void testDiagonalWin();
    void testDraw1();
    void testDraw2();
    void testDraw3();
    void testDraw4();
    void testDraw5();
    void testComputerMoves();
    void testGameAgainstComputer();
    void testExpandTopLeftCorner();
    void testExpandTopRightCorner();
    void testExpandBottomLeftCorner();
    void testExpandBottomRightCorner();
    void testIgnoreExpansionAtMaxSize();
    void testMaxExpansionAndWin();
    void testExpandFullBoard();
    void cleanupTestCase();
    void testMemoryLeak();

private:
    GameBoard *board;
};

#endif // TESTGAMEBOARD_H
