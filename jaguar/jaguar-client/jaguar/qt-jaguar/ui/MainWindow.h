/* 
 * File:   MainWindow.h
 * Author: cross
 *
 * Created on January 29, 2010, 3:11 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
private:
    Ui::MainWindow widget;
};

#endif	/* _MAINWINDOW_H */
