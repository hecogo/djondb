/*
 * File:   Radicacion.cpp
 * Author: cross
 *
 * Created on February 24, 2010, 10:14 PM
 */

#include "Radicacion.h"
#include "ui/TextSimple.h"

Radicacion::Radicacion(QWidget* parent, Qt::WindowFlags flags) : ScreenBase(parent, flags) {
    addRow("Test", new TextSimple());
    addRow("Test2", new TextSimple());
    addRow("Test3", new TextSimple());
    addRow("Test4", new TextSimple());

    addAction("Action1");
    addAction("Action2");
    addAction("Action3");
}

Radicacion::~Radicacion() {
}
