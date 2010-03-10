/* 
 * File:   ScreenBase.h
 * Author: cross
 *
 * Created on February 24, 2010, 10:14 PM
 */

#ifndef _SCREENBASE_H
#define	_SCREENBASE_H

#include <QWidget>
#include <QToolBar>
#include <QFormLayout>

#include "ui/freeformlayout.h"
#include "ui/GenericControl.h"

class ScreenBase : public QWidget {
    Q_OBJECT
public:
    ScreenBase(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~ScreenBase();
    void addAction(QString action);
protected:
    void addRow(QString label, QWidget* widget);
private:
    QToolBar* m_toolBar;
    FreeFormLayout* m_formLayout;
};

#endif	/* _SCREENBASE_H */

