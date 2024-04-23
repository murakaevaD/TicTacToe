#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSignalMapper>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    board = new GameBoard(3);
    gridLayout = new QGridLayout;

    QWidget *widget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    createBoard();
    createResetButton();
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(resetButton);
}

void MainWindow::createBoard() {
    buttons.resize(board->size(), std::vector<QPushButton*>(board->size()));
    for (int row = 0; row < board->size(); ++row) {
        for (int col = 0; col < board->size(); ++col) {
            QPushButton *button = new QPushButton("");
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setFont(QFont("Arial", 24));
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;
            connect(button, &QPushButton::clicked, this, [this, row, col] { handleButton(row, col); });
        }
    }
}

void MainWindow::createResetButton() {
    resetButton = new QPushButton("Restart Game");
    resetButton->setFont(QFont("Arial", 16));
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);
}

void MainWindow::resetGame() {
    for (int row = 0; row < board->size(); ++row) {
        for (int col = 0; col < board->size(); ++col) {
            buttons[row][col]->setText("");
            buttons[row][col]->setEnabled(true);
        }
    }
    delete board;
    board = new GameBoard(3);
}

void MainWindow::handleButton(int row, int col) {
    if (board->getPlayerAt(row, col) == Player::None) {
        board->makeMove(row, col);
        updateButton(buttons[row][col], row, col);
        if (board->checkWin()) {
            QMessageBox::information(this, "Game Over", "Player " + QString(board->currentPlayer() == Player::X ? "O" : "X") + " wins!");
            for (auto &row : buttons) {
                for (auto &button : row) {
                    button->setEnabled(false);
                }
            }
        } else if (board->isBoardFull()) {
            QMessageBox::information(this, "Game Over", "It is a draw!");
            for (auto &row : buttons) {
                for (auto &button : row) {
                    button->setEnabled(false);
                }
            }
        }
    }
}


void MainWindow::updateButton(QPushButton *button, int row, int col) {
    Player player = board->getPlayerAt(row, col);
    if (player != Player::None) {
        button->setText(player == Player::X ? "X" : "O");
        button->setEnabled(false);
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete board;
}
