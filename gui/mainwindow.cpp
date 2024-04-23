#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSignalMapper>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    board = new GameBoard(3); // Можно сделать размер доски настраиваемым
    gridLayout = new QGridLayout;

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    widget->setLayout(gridLayout);

    createBoard();
}

MainWindow::~MainWindow() {
    delete ui;
    delete board;
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

void MainWindow::handleButton(int row, int col) {
    if (board->getPlayerAt(row, col) == Player::None) {
        board->makeMove(row, col);
        updateButton(buttons[row][col], row, col);
        if (board->checkWin()) {
            QMessageBox::information(this, "Game Over", "Player " + QString(board->currentPlayer() == Player::X ? "O" : "X") + " wins!");
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
