#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "gameboard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButton(int row, int column);

private:
    void setupUi();
    void createGameBoard(int size);

    GameBoard *gameBoard;
    QVector<QVector<QPushButton*>> buttons;
    int boardSize;
};

#endif // MAINWINDOW_H
