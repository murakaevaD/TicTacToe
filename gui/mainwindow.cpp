#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);

    setupMenuUI();
    setupGameUI();

    centralLayout->addWidget(menuWidget);
    centralLayout->addWidget(gameWidget);

    menuWidget->show();
    gameWidget->hide();

    setCentralWidget(centralWidget);
}


MainWindow::~MainWindow() {
    delete ui;
    delete board;
}

void MainWindow::setupMenuUI() {
    menuWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(menuWidget);

    QGroupBox *modeGroup = new QGroupBox("Режим игры:");
    QVBoxLayout *modeLayout = new QVBoxLayout(modeGroup);
    expandingFieldButton = new QRadioButton("Расширяющееся поле");
    fixedFieldButton = new QRadioButton("Фиксированное поле");
    modeLayout->addWidget(expandingFieldButton);
    modeLayout->addWidget(fixedFieldButton);

    sizeLabel = new QLabel("Размер игрового поля:");
    sizeSpinBox = new QSpinBox();
    sizeSpinBox->setRange(3, 10);
    sizeSpinBox->setValue(3);

    QGroupBox *playerGroup = new QGroupBox("Играть за:");
    QVBoxLayout *playerLayout = new QVBoxLayout(playerGroup);
    playerXButton = new QRadioButton("X");
    playerOButton = new QRadioButton("O");
    playerLayout->addWidget(playerXButton);
    playerLayout->addWidget(playerOButton);

    QGroupBox *opponentGroup = new QGroupBox("Соперник:");
    QVBoxLayout *opponentLayout = new QVBoxLayout(opponentGroup);
    humanButton = new QRadioButton("Человек");
    computerButton = new QRadioButton("Компьютер");
    opponentLayout->addWidget(humanButton);
    opponentLayout->addWidget(computerButton);

    QPushButton *startButton = new QPushButton("Новая Игра");
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startNewGame);

    layout->addWidget(modeGroup);
    layout->addWidget(sizeLabel);
    layout->addWidget(sizeSpinBox);
    layout->addWidget(playerGroup);
    layout->addWidget(opponentGroup);
    layout->addWidget(startButton);

    menuWidget->setLayout(layout);
}

void MainWindow::setupGameUI() {
    gameWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(gameWidget);

    newGameButton = new QPushButton("Новая игра");
    QPushButton *surrenderButton = new QPushButton("Сдаться");
    QPushButton *restartButton = new QPushButton("Перезапуск");

    turnStatusLabel = new QLabel("Ход: X");

    gridLayout = new QGridLayout();
    layout->addWidget(newGameButton);
    layout->addWidget(turnStatusLabel);
    layout->addLayout(gridLayout);
    layout->addWidget(surrenderButton);
    layout->addWidget(restartButton);

    connect(newGameButton, &QPushButton::clicked, [this]() {
        menuWidget->show();
        gameWidget->hide();
    });
    connect(surrenderButton, &QPushButton::clicked, this, &MainWindow::handleSurrender);
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::restartGame);

    gameWidget->setLayout(layout);
    gameWidget->hide();
}


void MainWindow::startNewGame() {
    menuWidget->hide();
    gameWidget->show();

    int boardSize = sizeSpinBox->value();
    againstHuman = humanButton->isChecked();

    if (board) {
        delete board;
    }
    board = new GameBoard(boardSize);

    if (!againstHuman) {
        Player startingPlayer = playerXButton->isChecked() ? Player::X : Player::O;
        board->setCurrentPlayer(startingPlayer);
        if (playerOButton->isChecked()) {
            board->setCurrentPlayer(Player::X);
            QTimer::singleShot(300, this, &MainWindow::computerMove);
        }
    } else {
        board->setCurrentPlayer(Player::X);
    }

    clearBoard();
    createBoard();
    updateStatusLabel();
}


void MainWindow::createBoard() {
    const int boardSize = board->size();
    buttons.resize(boardSize, std::vector<QPushButton*>(boardSize));
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            QPushButton *button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setFont(QFont("Arial", 24));
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;

            connect(button, &QPushButton::clicked, [this, row, col](){
                handleButton(row, col);
            });
        }
    }
}

void MainWindow::handleButton(int row, int col) {
    if (board && board->getPlayerAt(row, col) == Player::None) {
        board->makeMove(row, col);
        updateBoard();
        if (board->checkWin() || board->isBoardFull()) {
            finalizeGame();
        } else {
            updateStatusLabel();
            if (!againstHuman) {
                QTimer::singleShot(300, this, &MainWindow::computerMove);
            }
        }
    }
}


void MainWindow::computerMove() {
    board->makeRandomMove();
    updateBoard();
    if (board->checkWin() || board->isBoardFull()) {
        finalizeGame();
    } else {
        updateStatusLabel();
    }
}

void MainWindow::finalizeGame() {
    if (board->checkWin()){
        QString winner = (board->currentPlayer() == Player::X ? "O" : "X");
        QMessageBox::information(this, "Game Over", "Player " + winner + " wins!");
        disableBoard();
    }
    if (board->isBoardFull()){
        QMessageBox::information(this, "Game Over", "It is a draw!");
    }
}

void MainWindow::updateStatusLabel() {
    if (board) {
        turnStatusLabel->setText("Turn: " + QString(board->currentPlayer() == Player::X ? "X" : "O"));
    }
}

void MainWindow::disableBoard() {
    for (auto &row : buttons) {
        for (auto &button : row) {
            button->setEnabled(false);
        }
    }
}

void MainWindow::handleSurrender() {
    if (board) {
        QString loser = (board->currentPlayer() == Player::X ? "X" : "O");
        QMessageBox::information(this, "Game Over", "Player " + loser + " surrenders!");
        disableBoard();
    }
}

void MainWindow::restartGame() {
    startNewGame();
}

void MainWindow::clearBoard() {
    for (auto &row : buttons) {
        for (auto &button : row) {
            button->setText("");
            button->setEnabled(true);
        }
    }
}

void MainWindow::updateBoard() {
    for (int row = 0; row < board->size(); ++row) {
        for (int col = 0; col < board->size(); ++col) {
            QPushButton *button = buttons[row][col];
            Player player = board->getPlayerAt(row, col);
            button->setText(player == Player::X ? "X" : (player == Player::O ? "O" : ""));
            button->setEnabled(player == Player::None);
        }
    }
}
