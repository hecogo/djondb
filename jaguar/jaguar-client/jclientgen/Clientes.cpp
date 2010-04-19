/*
 * File:   Clientes.cpp
 * Author: cross
 *
 * Created on February 24, 2010, 10:14 PM
 */

#include "Clientes.h"
#include "ui/TextSimple.h"

Clientes::Clientes(QWidget* parent, Qt::WindowFlags flags) : ScreenBase(parent, flags) {
    TextSimple* s1 = new TextSimple();
    s1->setEndLine(true);
    addRow("Name", s1);
    TextSimple* s2 = new TextSimple();
    s2->setEndLine(true);
    addRow("Last Name", s2);
    TextSimple* s3 = new TextSimple();
    s3->setEndLine(true);
    addRow("Birth Date", s3);
    TextSimple* s4 = new TextSimple();
    s4->setEndLine(true);
    addRow("Address", s4);
    TextSimple* s5 = new TextSimple();
    s5->setEndLine(true);
    addRow("Phone Number", s5);

    addAction("Action1", SLOT(action1));
}

Clientes::~Clientes() {
}

void Clientes::action1() {
    qDebug("Action1");
}