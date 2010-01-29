/* 
 * File:   CurrentDateTime.h
 * Author: cross
 *
 * Created on January 29, 2010, 4:32 PM
 */

#ifndef _CURRENTDATETIME_H
#define	_CURRENTDATETIME_H

#include "ui_CurrentDateTime.h"
#include <QTimer>

class CurrentDateTime : public QWidget {
    Q_OBJECT
public:
    CurrentDateTime();
    virtual ~CurrentDateTime();
    void start(int millisecs);
    void stop();
private:
    Ui::CurrentDateTime widget;
    void updateDateTime();

    QTimer* m_timer;

public slots:
    void timeout();


};

#endif	/* _CURRENTDATETIME_H */
