#include "Radicacion.h"
#include "ui/TextSimple.h"
#include "networkclient.h"

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
    Request* req = new Request(1);
    req->addParameter("ACT ", new string("NEW"));
    req->addParameter("DEFI", new string("1"));
    Response* response = sendReceive("localhost", 1043, req);
    string* data = response->getData();
    qDebug(data->c_str());
}