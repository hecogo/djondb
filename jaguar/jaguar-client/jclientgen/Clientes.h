/* 
 * File:   Clientes.h
 * Author: cross
 *
 * Created on April 11, 2010, 5:26 PM
 */

#ifndef _CLIENTES_H
#define	_CLIENTES_H

#include "ScreenBase.h"

class Clientes : public ScreenBase {
    Q_OBJECT
public:
    Clientes(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    virtual ~Clientes();

public slots:
    void action1();
private:

};

#endif	/* _CLIENTES_H */

