/* 
 * File:   MenuItem.h
 * Author: cross
 *
 * Created on February 8, 2010, 1:39 PM
 */

#ifndef _MENUITEM_H
#define	_MENUITEM_H

#include <QStandardItem>
#include <string>

class MenuItem : public QStandardItem {
public:
    MenuItem(std::string text, int value);
    MenuItem(const MenuItem& orig);
    virtual ~MenuItem();

    int value();
    
private:
    int _value;


};

#endif	/* _MENUITEM_H */

