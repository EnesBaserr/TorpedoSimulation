#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <iostream>
#include <thread>
#include "mainwindow.h"
#include <QTimer>

int main(int argc, char *argv[])

{
    QApplication app(argc, argv);

        MainWindow myMainWindow; // Create an instance of the MainWindow
        myMainWindow.setWindowTitle("Torpedo Simulation");


        myMainWindow.show();




        return app.exec();
    }
