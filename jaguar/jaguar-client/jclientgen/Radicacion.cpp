/*
 * File:   Radicacion.cpp
 * Author: cross
 *
 * Created on February 24, 2010, 10:14 PM
 */

#include "Radicacion.h"
#include "ui/TextSimple.h"

TextSimple* createText(bool endLine) {
    TextSimple* s = new TextSimple();
    s->setEndLine(endLine);
    return s;
}

Radicacion::Radicacion(QWidget* parent, Qt::WindowFlags flags) : ScreenBase(parent, flags) {
    addRow("Test", createText(true));
    addRow("Test", createText(false));
    addRow("Test", createText(true));
    addRow("Test", createText(false));
    addRow("Test", createText(true));

    addAction("Action1", SLOT(action1));
    addAction("Action2", SLOT(action1));
    addAction("Action3", SLOT(action1));
    // 0001ACT 03NEWDEFI011FFFF
}

Radicacion::~Radicacion() {
}

void Radicacion::action1() {
    qDebug("Action1");
}