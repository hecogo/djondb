/* 
 * File:   CrearClientes.h
 * Author: cross
 *
 * Created on February 9, 2010, 1:23 PM
 */

#ifndef _CREARCLIENTES_H
#define	_CREARCLIENTES_H

#include "ui_CrearClientes.h"

class CrearClientes : public QWidget {
    Q_OBJECT
public:
    CrearClientes();
    virtual ~CrearClientes();
private:
    Ui::CrearClientes widget;
};

#endif	/* _CREARCLIENTES_H */
