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
    virtual bool endLine();
    virtual void setEndLine(bool);

public slots:
    bool validate();

private:
    bool m_endLine;
};

#endif	/* _TEXTSIMPLE_H */

