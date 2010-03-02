/* 
 * File:   TextSimple.h
 * Author: cross
 *
 * Created on February 11, 2010, 1:34 PM
 */

#ifndef _TEXTSIMPLE_H
#define	_TEXTSIMPLE_H

#include "GenericControl.h"
#include <QLineEdit>

class TextSimple : public QLineEdit, public GenericControl {
Q_OBJECT
public:
    TextSimple();
    virtual ~TextSimple();

public slots:
    bool validate();
};

#endif	/* _TEXTSIMPLE_H */

