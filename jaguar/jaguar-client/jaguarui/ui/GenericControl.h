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

private:
    bool m_endLine;
    
public:
    GenericControl();
    virtual ~GenericControl();

    virtual bool validate() = 0;
    bool endLine();
    
    void setEndLine(bool);
};

#endif	/* _GENERICCONTROL_H */

