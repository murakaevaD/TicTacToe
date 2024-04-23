#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include "gameboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



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
    Ui::MainWindow *ui;
    GameBoard *board;
    QGridLayout *gridLayout;
    QPushButton *resetButton;
    QSpinBox *sizeSpinBox;
    QPushButton *newGameButton;
    std::vector<std::vector<QPushButton*>> buttons;
    void setupInitialUI();
    void createBoard();
    void updateButton(QPushButton *button, int row, int col);
    void clearBoard();
};


#endif
