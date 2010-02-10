/* 
 * File:   MenuItem.cpp
 * Author: cross
 * 
 * Created on February 8, 2010, 1:39 PM
 */

#include "MenuItem.h"

MenuItem::MenuItem(std::string text, int value) {
    setText(QString(text.c_str()));
    setEditable(false);
    _value = value;
}

MenuItem::MenuItem(const MenuItem& orig) : QStandardItem(orig) {
}

MenuItem::~MenuItem() {
}

int MenuItem::value() {
    return _value;
}