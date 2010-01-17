/*
 * File:   main.cpp
 * Author: cross
 *
 * Created on January 12, 2010, 9:17 PM
 */

#include <QtGui/QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    MainWindow* main = new MainWindow();
    main->setGeometry(0, 0, 800, 600);
    main->show();
    // create and show your widgets here

    return app.exec();
}
