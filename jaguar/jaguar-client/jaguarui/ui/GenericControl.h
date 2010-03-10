/* 
 * File:   GenericControl.h
 * Author: cross
 *
 * Created on February 11, 2010, 1:29 PM
 */

#ifndef _GENERICCONTROL_H
#define	_GENERICCONTROL_H

#include <QWidget>

class GenericControl {

public:
    GenericControl();
    GenericControl(const GenericControl& orig);
    ~GenericControl();

    virtual bool validate() = 0;
    virtual bool endLine() = 0;
    virtual void setEndLine(bool) = 0;
};

#endif	/* _GENERICCONTROL_H */

