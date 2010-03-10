/* 
 * File:   TextSimple.cpp
 * Author: cross
 * 
 * Created on February 11, 2010, 1:34 PM
 */

#include "TextSimple.h"

TextSimple::TextSimple() : QLineEdit() {
}

TextSimple::~TextSimple() {
}

bool TextSimple::validate() {
    return true;
}

bool TextSimple::endLine() {
    return m_endLine;
}

void TextSimple::setEndLine(bool endLine) {
    m_endLine = endLine;
}


