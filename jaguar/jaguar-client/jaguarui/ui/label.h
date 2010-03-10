/* 
 * File:   label.h
 * Author: cross
 *
 * Created on March 2, 2010, 7:40 PM
 */

#ifndef _LABEL_H
#define	_LABEL_H

#include "GenericControl.h"
#include <QLabel>

class Label : public QLabel, public GenericControl {

public:
    Label(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);
    virtual bool validate();
    virtual bool endLine();
    virtual void setEndLine(bool);

private:
    bool m_endLine;
};

#endif	/* _LABEL_H */

