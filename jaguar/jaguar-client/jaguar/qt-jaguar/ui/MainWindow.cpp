/*
 * File:   MainWindow.cpp
 * Author: cross
 *
 * Created on January 29, 2010, 3:11 PM
 */

#include "MainWindow.h"
#include "components/CurrentDateTime.h"

MainWindow::MainWindow() {
    widget.setupUi(this);

    CurrentDateTime* time = new CurrentDateTime();
    //time->setLayoutDirection(Qt::RightToLeft);
//    widget.statusBarLayout->addWidget(time);
    widget.statusbar->addPermanentWidget(time);
    time->setVisible(true);
    time->start(1000);

}

MainWindow::~MainWindow() {
}
