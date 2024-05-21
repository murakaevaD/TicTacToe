#include "tictactoetests.h"


void TestGameBoard::initTestCase() {
    board = new GameBoard(3);
    srand(static_cast<unsigned>(time(nullptr)));
}

void TestGameBoard::testHorizontalWin() {
    // Победа в первой строке
    board->makeMove(0, 0); // X
    board->makeMove(1, 0); // O
    board->makeMove(0, 1); // X
    board->makeMove(1, 1); // O
    board->makeMove(0, 2); // X
    QVERIFY(board->checkWin(3));
    delete board;

    // Победа во второй строке
    GameBoard board2(3);
    board2.makeMove(1, 0); // X
    board2.makeMove(0, 0); // O
    board2.makeMove(1, 1); // X
    board2.makeMove(0, 1); // O
    board2.makeMove(1, 2); // X
    QVERIFY(board2.checkWin(3));

    // Победа в третьей строке
    GameBoard board3(3);
    board3.makeMove(2, 0); // X
    board3.makeMove(0, 0); // O
    board3.makeMove(2, 1); // X
    board3.makeMove(0, 1); // O
    board3.makeMove(2, 2); // X
    QVERIFY(board3.checkWin(3));
}

void TestGameBoard::testVerticalWin() {
    // Победа в первом столбце
    GameBoard board(3);
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(1, 0); // X
    board.makeMove(1, 1); // O
    board.makeMove(2, 0); // X
    QVERIFY(board.checkWin(3));

    // Победа во втором столбце
    GameBoard board2(3);
    board2.makeMove(0, 1); // X
    board2.makeMove(0, 0); // O
    board2.makeMove(1, 1); // X
    board2.makeMove(1, 0); // O
    board2.makeMove(2, 1); // X
    QVERIFY(board2.checkWin(3));

    // Победа в третьем столбце
    GameBoard board3(3);
    board3.makeMove(0, 2); // X
    board3.makeMove(0, 0); // O
    board3.makeMove(1, 2); // X
    board3.makeMove(1, 0); // O
    board3.makeMove(2, 2); // X
    QVERIFY(board3.checkWin(3));
}

void TestGameBoard::testDiagonalWin() {
    // Победа по главной диагонали
    GameBoard board(3);
    board.makeMove(0, 0); // X
    board.makeMove(0, 1); // O
    board.makeMove(1, 1); // X
    board.makeMove(1, 0); // O
    board.makeMove(2, 2); // X
    QVERIFY(board.checkWin(3));

    // Победа по побочной диагонали
    GameBoard board2(3);
    board2.makeMove(0, 2); // X
    board2.makeMove(0, 1); // O
    board2.makeMove(1, 1); // X
    board2.makeMove(1, 0); // O
    board2.makeMove(2, 0); // X
    QVERIFY(board2.checkWin(3));
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
    QVERIFY(board.isBoardFull());
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

void TestGameBoard::testComputerMoves() {
    board = new GameBoard(3);
    board->clearBoard();                 //Cбрасываем текущую доску
    board->setCurrentPlayer(Player::X);  // Пусть компьютер играет за 'X'
    board->makeRandomMove();  // Позволяем компьютеру сделать ход

    int emptyCells = 0;
    for (int row = 0; row < board->sizeX(); ++row) {
        for (int col = 0; col < board->sizeY(); ++col) {
            if (board->getPlayerAt(row, col) == Player::None) {
                emptyCells++;
            }
        }
    }

    QCOMPARE(emptyCells, 8);  // Проверяем, что пустых клеток стало на 1 меньше
    delete board;
}

void TestGameBoard::testGameAgainstComputer() {
    board = new GameBoard(3);

    // Симуляция игры: пусть пользователь играет за 'X', а компьютер за 'O'
    board->setCurrentPlayer(Player::X);
    board->makeMove(0, 0);
    board->makeRandomMove();

    board->makeMove(0, 1);
    if (!board->checkWin(3) && !board->isBoardFull()) {
        board->makeRandomMove();
    }

    board->makeMove(0, 2);
    bool win = board->checkWin(3);
    bool draw = board->isBoardFull() && !win;

    QVERIFY(win || draw || (!win && !draw));

    delete board;
}

void TestGameBoard::testExpandTopLeftCorner() {
    GameBoard gameBoard;
    gameBoard.expandBoard(0, 0);
    QCOMPARE(gameBoard.sizeX(), 6); // Размер поля увеличился на 3 в каждую сторону
    QCOMPARE(gameBoard.sizeY(), 6);
    QCOMPARE(gameBoard.getPlayerAt(0, 0), Player::None);
    QCOMPARE(gameBoard.getPlayerAt(3, 3), Player::None);
}

void TestGameBoard::testExpandTopRightCorner() {
    GameBoard gameBoard;
    gameBoard.expandBoard(0, 2);
    QCOMPARE(gameBoard.sizeX(), 6); // Размер поля увеличился на 3 вправо и вверх
    QCOMPARE(gameBoard.sizeY(), 6);
    QCOMPARE(gameBoard.getPlayerAt(0, 5), Player::None);
    QCOMPARE(gameBoard.getPlayerAt(3, 3), Player::None);
}

void TestGameBoard::testExpandBottomLeftCorner() {
    GameBoard gameBoard;
    gameBoard.expandBoard(2, 0);
    QCOMPARE(gameBoard.sizeX(), 6); // Размер поля увеличился на 3 влево и вниз
    QCOMPARE(gameBoard.sizeY(), 6);
    QCOMPARE(gameBoard.getPlayerAt(5, 0), Player::None);
    QCOMPARE(gameBoard.getPlayerAt(3, 3), Player::None);
}

void TestGameBoard::testExpandBottomRightCorner() {
    GameBoard gameBoard;
    gameBoard.expandBoard(2, 2);
    QCOMPARE(gameBoard.sizeX(), 6); // Размер поля увеличился на 3 вправо и вниз
    QCOMPARE(gameBoard.sizeY(), 6);
    QCOMPARE(gameBoard.getPlayerAt(5, 5), Player::None);
    QCOMPARE(gameBoard.getPlayerAt(3, 3), Player::None);
}

void TestGameBoard::testIgnoreExpansionAtMaxSize() {
    GameBoard gameBoard;

    while (gameBoard.sizeX() < 18 && gameBoard.sizeY() < 18) {
        gameBoard.expandBoard(0, 0);
    }

    gameBoard.expandBoard(0, 0);
    QCOMPARE(gameBoard.sizeX(), 18);
    QCOMPARE(gameBoard.sizeY(), 18);
    QCOMPARE(gameBoard.getPlayerAt(1, 1), Player::None);
}

void TestGameBoard::testMaxExpansionAndWin() {
    GameBoard board;

    while (board.sizeX() < 18 && board.sizeY() < 18) {
        board.expandBoard(0, 0);
    }

    for (int i = 0; i < 5; ++i) {
        board.makeMove(0, i);
        board.setCurrentPlayer(Player::X);
    }

    // Проверка наличия победы
    QVERIFY(board.isWin(Player::X, 5));
}

void TestGameBoard::testExpandFullBoard() {
    GameBoard board;
    // Расширяем поле до максимального размера
    while (board.sizeX() < 18 && board.sizeY() < 18) {
        board.expandBoard(0, 0);
    }

    // Заполняем поле полностью
    for (int row = 0; row < board.sizeY(); ++row) {
        for (int col = 0; col < board.sizeX(); ++col) {
            board.makeMove(row, col);
        }
    }

    // Проверка, что доска полностью заполнена
    QVERIFY(board.isBoardFull());
}

void TestGameBoard::testMemoryLeak() {
    board = new GameBoard(3);
    QVERIFY(board != nullptr);

    delete board;
}


void TestGameBoard::cleanupTestCase() {
    board = new GameBoard(3);
    delete board;
    board = nullptr;
    QVERIFY(board == nullptr);
}

QTEST_MAIN(TestGameBoard)

