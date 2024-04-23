#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), boardSize(3) {
    setupUi();
    createGameBoard(boardSize);
}

MainWindow::~MainWindow() {
    for (auto &row : buttons) {
        for (auto *button : row) {
            delete button;
        }
    }
    delete gameBoard;
    delete resetButton;
    delete winnerButton;
}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QGridLayout *layout = new QGridLayout(centralWidget);

    for (int i = 0; i < boardSize; i++) {
        QVector<QPushButton*> buttonRow;
        for (int j = 0; j < boardSize; j++) {
            QPushButton *button = new QPushButton(" ", this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            layout->addWidget(button, i, j);
            buttonRow.push_back(button);
            connect(button, &QPushButton::clicked, this, [this, i, j] { handleButton(i, j); });
        }
        buttons.push_back(buttonRow);
    }
    resetButton = new QPushButton("Reset Game", this);
    layout->addWidget(resetButton, boardSize, 0, 1, boardSize);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    winnerButton = new QPushButton("Announce Winner", this);
    layout->addWidget(winnerButton, boardSize + 1, 0, 1, boardSize);
    connect(winnerButton, &QPushButton::clicked, this, &MainWindow::announceWinner);
}

void MainWindow::createGameBoard(int size) {

}

void MainWindow::handleButton(int row, int column) {

}

void MainWindow::resetGame() {

}

void MainWindow::announceWinner() {

}
