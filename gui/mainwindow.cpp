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
}

void MainWindow::createGameBoard(int size) {

}

void MainWindow::handleButton(int row, int column) {

}

