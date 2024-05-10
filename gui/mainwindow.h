// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>
#include "gameboard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startNewGame();
    void handleButton(int row, int col);
    void computerMove();
    void restartGame();
    void updateBoard();

private:
    QWidget *menuWidget;
    QWidget *gameWidget;
    QRadioButton *expandingFieldButton;
    QRadioButton *fixedFieldButton;
    QLabel *sizeLabel;
    QSpinBox *sizeSpinBox;
    QLabel *winConditionLabel;
    QSpinBox *winConditionSpinBox;
    QRadioButton *playerXButton;
    QRadioButton *playerOButton;
    QRadioButton *humanButton;
    QRadioButton *computerButton;
    QPushButton *newGameButton;
    QLabel *turnStatusLabel;
    QGridLayout *gridLayout;
    GameBoard *board;
    std::vector<std::vector<QPushButton*>> buttons;
    bool againstHuman;

    void setupMenuUI();
    void setupGameUI();
    void finalizeGame();
    void updateStatusLabel();
    void disableBoard();
    void handleSurrender();
    void createBoard();
    void resizeButtons(int newSize);
};

#endif // MAINWINDOW_H
