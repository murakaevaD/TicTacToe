#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSpinBox>
#include "gameboard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButton(int row, int col);
    void resetGame();
    void startNewGame();

private:
    GameBoard *board;
    QGridLayout *gridLayout;
    QPushButton *resetButton;
    QPushButton *newGameButton;
    std::vector<std::vector<QPushButton*>> buttons;

    void setupInitialUI();
    void createBoard(int size, bool infinite);
    void updateButton(QPushButton *button, int row, int col);
    void clearBoard();
    void setupGameOptions();
};

#endif
