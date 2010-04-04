/* 
 * File:   TextSimple.cpp
 * Author: cross
 * 
 * Created on February 11, 2010, 1:34 PM
 */

#include "TextSimple.h"

TextSimple::TextSimple() : QLineEdit(), GenericControl() {
}

TextSimple::~TextSimple() {
}

bool TextSimple::validate() {
    return true;
}
