#ifndef TESTGAMEBOARD_H
#define TESTGAMEBOARD_H

#include <QtTest>

class TestGameBoard : public QObject {
    Q_OBJECT

private slots:
    void testHorizontalWin();
    void testVerticalWin();
    void testDiagonalWin();
    void testDraw1();
    void testDraw2();
    void testDraw3();
    void testDraw4();
    void testDraw5();
};

#endif // TESTGAMEBOARD_H
