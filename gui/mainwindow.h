#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include "gameboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startNewGame();
    void handleSurrender();
    void restartGame();
    void handleButton(int row, int col);

private:
    Ui::MainWindow *ui;
    QWidget *menuWidget;
    QWidget *gameWidget;
    GameBoard *board;
    std::vector<std::vector<QPushButton*>> buttons;
    QLabel *turnStatusLabel;
    QLabel *sizeLabel;
    QSpinBox *sizeSpinBox;
    QRadioButton *expandingFieldButton;
    QRadioButton *fixedFieldButton;
    QRadioButton *playerXButton;
    QRadioButton *playerOButton;
    QRadioButton *humanButton;
    QRadioButton *computerButton;
    QPushButton *newGameButton;
    QGridLayout *gridLayout;
    bool againstHuman;

    void setupMenuUI();
    void setupGameUI();
    void clearBoard();
    void createBoard();
    void updateStatusLabel();
    void disableBoard();
    void computerMove();
    void finalizeGame();
    void updateBoard();
};

#endif
