/*
 * File:   main.cpp
 * Author: cross
 *
 * Created on January 29, 2010, 3:07 PM
 */

#include <QtGui/QApplication>

#include "ui/MainWindow.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    MainWindow* window = new MainWindow();
    window->show();
    // create and show your widgets here

    return app.exec();
}
