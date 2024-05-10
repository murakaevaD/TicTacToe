#include <QApplication>
#include "mainwindow.h"
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    srand(static_cast<unsigned int>(time(nullptr)));

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
