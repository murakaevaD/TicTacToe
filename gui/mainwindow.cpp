#include "mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), menuWidget(nullptr), gameWidget(nullptr), expandingFieldButton(nullptr),
    fixedFieldButton(nullptr), sizeLabel(nullptr), sizeSpinBox(nullptr), winConditionLabel(nullptr), winConditionSpinBox(nullptr),
    playerXButton(nullptr), playerOButton(nullptr), humanButton(nullptr), computerButton(nullptr), newGameButton(nullptr),
    turnStatusLabel(nullptr), gridLayout(nullptr), board(nullptr), againstHuman(true) {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);

    setupMenuUI();
    setupGameUI();

    centralLayout->addWidget(menuWidget);
    centralLayout->addWidget(gameWidget);

    menuWidget->show();
    gameWidget->hide();

    setCentralWidget(centralWidget);

    this->showMaximized();
}

MainWindow::~MainWindow() {
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

    winConditionLabel = new QLabel("Количество символов для победы:");
    winConditionSpinBox = new QSpinBox();
    winConditionSpinBox->setRange(3, 18);
    winConditionSpinBox->setValue(3);

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

    connect(fixedFieldButton, &QRadioButton::clicked, this, &MainWindow::toggleFixedField);
    connect(expandingFieldButton, &QRadioButton::clicked, this, &MainWindow::toggleExpandingField);

    layout->addWidget(modeGroup);
    layout->addWidget(sizeLabel);
    layout->addWidget(sizeSpinBox);
    layout->addWidget(winConditionLabel);
    layout->addWidget(winConditionSpinBox);
    layout->addWidget(playerGroup);
    layout->addWidget(opponentGroup);
    layout->addWidget(startButton);

    menuWidget->setLayout(layout);
}

void MainWindow::toggleFixedField() {
    winConditionSpinBox->setEnabled(false);
    winConditionSpinBox->setValue(3);
    sizeSpinBox->setEnabled(true);
    computerButton->setEnabled(true);
    humanButton->setChecked(false);
}

void MainWindow::toggleExpandingField() {
    winConditionSpinBox->setEnabled(true);
    sizeSpinBox->setEnabled(false);
    sizeSpinBox->setValue(3);
    computerButton->setEnabled(false);
    humanButton->setChecked(true);
}

void MainWindow::toggleSurrenderButton() {
    surrenderButton->setEnabled(false);
}

void MainWindow::untoggleSurrenderButton() {
    surrenderButton->setEnabled(true);
}

void MainWindow::setupGameUI() {
    gameWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(gameWidget);

    newGameButton = new QPushButton("Новая игра");
    surrenderButton = new QPushButton("Сдаться");
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
        handleBoard();
    });
    connect(surrenderButton, &QPushButton::clicked, this, &MainWindow::handleSurrender);
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::handleBoard);

    gameWidget->setLayout(layout);
    gameWidget->hide();
}

void MainWindow::startNewGame() {
    menuWidget->hide();
    gameWidget->show();

    if (board) {
        delete board;
    }
    board = new GameBoard(sizeSpinBox->value());

    if (expandingFieldButton->isChecked()){
        board->setExpandingMode(true);
        winConditions = winConditionSpinBox->value();
    } else{
        winConditions = board->size();
    }

    againstHuman = humanButton->isChecked();
    if (!againstHuman) {
        Player startingPlayer = playerXButton->isChecked() ? Player::X : Player::O;
        board->setCurrentPlayer(startingPlayer);
        if (playerOButton->isChecked()) {
            board->setCurrentPlayer(Player::X);
            QTimer::singleShot(300, this, &MainWindow::computerMove);
        }
    } else {
        Player startingPlayer = playerXButton->isChecked() ? Player::X : Player::O;
        board->setCurrentPlayer(startingPlayer);
    }

    board->clearBoard();
    handleBoard();
    updateStatusLabel();
}

void MainWindow::handleButton(int row, int col) {
    if (board && board->getPlayerAt(row, col) == Player::None) {
        board->makeMove(row, col);
        updateBoard();
        if (board->checkWin(winConditions) || board->isBoardFull()) {
            finalizeGame();
            toggleSurrenderButton();
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
    if (board->checkWin(winConditions) || board->isBoardFull()) {
        finalizeGame();
    } else {
        updateStatusLabel();
    }
}

void MainWindow::finalizeGame() {
    if (board->checkWin(winConditions)){
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
    toggleSurrenderButton();
}

void MainWindow::handleBoard() {
    if (expandingFieldButton->isChecked()) {
        if (board) {
            delete board;
        }
        board = new GameBoard(3);
        board->setExpandingMode(true);
    } else {
        board->clearBoard();
    }

    board->setCurrentPlayer(Player::X);
    updateBoard();
    updateStatusLabel();
    untoggleSurrenderButton();
}

void MainWindow::updateBoard() {
    int boardSize = board->size();

    resizeButtons(boardSize);
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            QPushButton *button = buttons[row][col];
            Player player = board->getPlayerAt(row, col);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setText(player == Player::X ? "X" : (player == Player::O ? "O" : ""));
            button->setEnabled(player == Player::None);
        }
    }
}

void MainWindow::resizeButtons(int newSize) {
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    buttons.clear();

    buttons.resize(newSize, std::vector<QPushButton*>(newSize, nullptr));
    for (int row = 0; row < newSize; ++row) {
        for (int col = 0; col < newSize; ++col) {
            QPushButton *button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setFont(QFont("Arial", 24));
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;
            connect(button, &QPushButton::clicked, [this, row, col]() {
                handleButton(row, col);
            });
        }
    }
}
