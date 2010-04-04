#include "label.h"

Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags f) : QLabel(text, parent, f), GenericControl() {
}

bool Label::validate() {
    return true;
}

