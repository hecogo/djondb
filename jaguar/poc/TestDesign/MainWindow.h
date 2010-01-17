/* 
 * File:   MainWindow.h
 * Author: cross
 *
 * Created on January 12, 2010, 9:22 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"
#include <QGraphicsView>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
private:
    Ui::MainWindow widget;

    QGraphicsView* m_view;
};

#endif	/* _MAINWINDOW_H */
