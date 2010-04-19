/* 
 * File:   Radicacion.h
 * Author: cross
 *
 * Created on February 24, 2010, 10:14 PM
 */

#ifndef _RADICACION_H
#define	_RADICACION_H

#include "ui_Radicacion.h"
#include "ScreenBase.h"

class Radicacion : public ScreenBase {
    Q_OBJECT
public:
    Radicacion(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~Radicacion();

public slots:
    void action1();
private:
};

#endif	/* _RADICACION_H */
