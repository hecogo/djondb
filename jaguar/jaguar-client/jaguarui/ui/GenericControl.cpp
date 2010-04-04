/* 
 * File:   GenericControl.cpp
 * Author: cross
 * 
 * Created on February 11, 2010, 1:29 PM
 */

#include "GenericControl.h"
#include <iostream>

GenericControl::GenericControl() {
    m_endLine = false;
}

GenericControl::~GenericControl() {
}

bool GenericControl::endLine() {
    return m_endLine;
}

void GenericControl::setEndLine(bool endLine) {
    m_endLine = endLine;
}
