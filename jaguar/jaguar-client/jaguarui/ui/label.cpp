#include "label.h"

Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags f) : QLabel(text, parent, f){
    setEndLine(false);
}

bool Label::validate() {
    return true;
}

bool Label::endLine() {
    return m_endLine;
}

void Label::setEndLine(bool endLine) {
    m_endLine = endLine;
}
