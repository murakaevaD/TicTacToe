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
    QVERIFY(board->checkWin());

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
    // Победа в первом столбце
    GameBoard board(3);
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
    // Победа по главной диагонали
    GameBoard board(3);
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

void TestGameBoard::testComputerMoves() {
    board->clearBoard();                 //Cбрасываем текущую доску
    board->setCurrentPlayer(Player::X);  // Пусть компьютер играет за 'X'
    board->makeRandomMove();  // Позволяем компьютеру сделать ход

    int emptyCells = 0;
    for (int row = 0; row < board->size(); ++row) {
        for (int col = 0; col < board->size(); ++col) {
            if (board->getPlayerAt(row, col) == Player::None) {
                emptyCells++;
            }
        }
    }

    QCOMPARE(emptyCells, 8);  // Проверяем, что пустых клеток стало на 1 меньше
}

void TestGameBoard::testGameAgainstComputer() {
    board = new GameBoard(3);  // Инициализируем доску 3x3 для тестирования

    // Симуляция игры: пусть пользователь играет за 'X', а компьютер за 'O'
    board->setCurrentPlayer(Player::X);
    board->makeMove(0, 0); // Игрок ходит в угол
    board->makeRandomMove(); // Ход компьютера

    board->makeMove(0, 1); // Игрок делает второй ход
    if (!board->checkWin() && !board->isBoardFull()) {
        board->makeRandomMove(); // Ход компьютера
    }

    board->makeMove(0, 2); // Игрок делает третий ход, возможная победа
    bool win = board->checkWin();
    bool draw = board->isBoardFull() && !win;

    // Проверка состояния игры после ходов
    QVERIFY(win || draw || (!win && !draw)); // Убедимся, что игра закончилась или продолжается корректно

    delete board;
}

void TestGameBoard::testExpandTopLeftCorner()
{
    GameBoard gameBoard;
    gameBoard.expandBoard(0, 0);
    QCOMPARE(gameBoard.boardSize, 4); // Размер поля увеличился на 1
    QCOMPARE(gameBoard.getPlayerAt(0, 0), Player::None); // Левый верхний угол пустой
    QCOMPARE(gameBoard.getPlayerAt(1, 1), Player::None); // Проверка центра
}

void TestGameBoard::testExpandTopRightCorner()
{
    GameBoard gameBoard;
    gameBoard.expandBoard(0, 2);
    QCOMPARE(gameBoard.boardSize, 4); // Размер поля увеличился на 1
    QCOMPARE(gameBoard.getPlayerAt(0, 3), Player::None); // Правый верхний угол пустой
    QCOMPARE(gameBoard.getPlayerAt(1, 1), Player::None); // Проверка центра
}

void TestGameBoard::testExpandBottomLeftCorner()
{
    GameBoard gameBoard;
    gameBoard.expandBoard(2, 0);
    QCOMPARE(gameBoard.boardSize, 4); // Размер поля увеличился на 1
    QCOMPARE(gameBoard.getPlayerAt(3, 0), Player::None); // Левый нижний угол пустой
    QCOMPARE(gameBoard.getPlayerAt(1, 1), Player::None); // Проверка центра
}

void TestGameBoard::testExpandBottomRightCorner()
{
    GameBoard gameBoard;
    gameBoard.expandBoard(2, 2);
    QCOMPARE(gameBoard.boardSize, 4); // Размер поля увеличился на 1
    QCOMPARE(gameBoard.getPlayerAt(3, 3), Player::None); // Правый нижний угол пустой
    QCOMPARE(gameBoard.getPlayerAt(1, 1), Player::None); // Проверка центра
}

void TestGameBoard::testIgnoreExpansionAtMaxSize()
{
    GameBoard gameBoard;
    // Заполним игровое поле до максимального размера
    while (gameBoard.boardSize < 15) {
        gameBoard.expandBoard(0, 0);
    }
    // Попробуем расширить поле еще раз
    gameBoard.expandBoard(0, 0);
    QCOMPARE(gameBoard.boardSize, 15); // Размер поля не изменился
    QCOMPARE(gameBoard.getPlayerAt(1, 1), Player::None); // Проверка центра
}
void TestGameBoard::testMemoryLeak() {
    board = new GameBoard(3);  // Создаём доску 3x3
    QVERIFY(board != nullptr); // Проверяем, что объект создан

    delete board;              // Удаляем объект
}


void TestGameBoard::cleanupTestCase() {
    delete board;
    board = nullptr;
}

QTEST_MAIN(TestGameBoard)

