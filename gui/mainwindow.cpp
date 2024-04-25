#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSignalMapper>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupInitialUI();
}

void MainWindow::setupInitialUI() {
    QWidget *widget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    sizeSpinBox = new QSpinBox();
    sizeSpinBox->setRange(3, 10);
    sizeSpinBox->setValue(3);
    newGameButton = new QPushButton("New Game");
    resetButton = new QPushButton("Reset Game");
    gridLayout = new QGridLayout();

    mainLayout->addWidget(new QLabel("Select board size:"));
    mainLayout->addWidget(sizeSpinBox);
    mainLayout->addWidget(newGameButton);
    mainLayout->addWidget(resetButton);
    mainLayout->addLayout(gridLayout);
    setCentralWidget(widget);

    connect(newGameButton, &QPushButton::clicked, this, &MainWindow::startNewGame);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);
    startNewGame();
}

void MainWindow::startNewGame() {
    clearBoard();
    board = new GameBoard(sizeSpinBox->value());
    createBoard();
}


void MainWindow::clearBoard() {
    for (auto &row : buttons) {
        for (auto &button : row) {
            gridLayout->removeWidget(button);
            delete button;
        }
    }
    buttons.clear();
}

void MainWindow::createBoard() {
    buttons.resize(board->size(), std::vector<QPushButton*>(board->size()));
    for (int row = 0; row < board->size(); ++row) {
        for (int col = 0; col < board->size(); ++col) {
            QPushButton *button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setFont(QFont("Arial", 24));
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;
            connect(button, &QPushButton::clicked, this, [this, row, col] { handleButton(row, col); });
        }
    }
}


void MainWindow::resetGame() {
    for (auto &row : buttons) {
        for (auto &button : row) {
            button->setText("");
            button->setEnabled(true);
        }
    }
    delete board;
    board = new GameBoard(sizeSpinBox->value());
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
    delete board;
}
