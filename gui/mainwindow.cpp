#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), boardSize(3) {
    setupUi();
    createGameBoard(boardSize);
}

MainWindow::~MainWindow() {

}

void MainWindow::setupUi() {

}

void MainWindow::createGameBoard(int size) {

}

void MainWindow::handleButton(int row, int column) {

}

