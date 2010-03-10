
#include <QLabel>
#include <QSizePolicy>
#include <QSize>
#include <qt4/QtCore/qdebug.h>
#include "freeformlayout.h"
#include "GenericControl.h"
#include "label.h"
#include <iostream>
#include <qt4/QtGui/qwidget.h>

using namespace std;

FreeFormLayout::FreeFormLayout(QWidget *parent) : QLayout(parent) {

}

FreeFormLayout::~FreeFormLayout() {

}

void FreeFormLayout::addItem(QLayoutItem *item) {
    bool endLine = ((GenericControl*)item->widget())->endLine();

    ItemWrapper* wrapper = new ItemWrapper(item, endLine);

    itemList.push_back(wrapper);
}

void FreeFormLayout::addItem(QWidget *item) {
    QLayout::addWidget(item);
    /*
    QWidgetItem* qitem = new QWidgetItem(item);

    ItemWrapper* wrapper = new ItemWrapper(qitem);
    itemList.push_back(wrapper);
    item->setVisible(true);
     */
}

QSize FreeFormLayout::sizeHint() const {
    return minimumSize();
}

void FreeFormLayout::setGeometry(const QRect &rect) {
    QLayout::setGeometry(rect);
    doLayout(rect);
}

QLayoutItem* FreeFormLayout::itemAt(int index) const {
    if (index >= 0 && index < itemList.size()) {
        ItemWrapper* wrapper = itemList.at(index);
        return wrapper->m_item;
    } else
        return 0;
}

QLayoutItem* FreeFormLayout::takeAt(int index) {
    if (index >= 0 && index < itemList.size()) {
        ItemWrapper* wrapper = itemList.takeAt(index);
        return wrapper->m_item;
    } else
        return 0;
}

int FreeFormLayout::doLayout(const QRect &rect) const {
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    ItemWrapper *wrapper;

    foreach(wrapper, itemList) {
        QLayoutItem* item = wrapper->m_item;
        QWidget *wid = item->widget();
        int spaceX = 1;
        if (spaceX == -1)
            spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        int spaceY = 1;
        if (spaceY == -1)
            spaceY = wid->style()->layoutSpacing(
                QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
        int nextX = x + item->sizeHint().width() + spaceX;
//        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
        if (wrapper->m_endLine) {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

void FreeFormLayout::addRow(QString label, QWidget* item, bool endLine) {
    Label* lbl = new Label(label);
    addItem(lbl);
    addItem(item);
}

int FreeFormLayout::count() const {
    int c =  itemList.size();
    cout << "count: " << c << endl;
    return c;
}

QSize FreeFormLayout::minimumSize() const {
    return QSize(200, 100);
}

QSize FreeFormLayout::maximumSize() const {
    return QSize(1000, 1000);
}

Qt::Orientations FreeFormLayout::expandingDirections() const {
    return Qt::Horizontal | Qt::Vertical;
}

QRect FreeFormLayout::geometry() const {
//    return QLayout::geometry();
}

bool FreeFormLayout::isEmpty() const {
    return (itemList.size() == 0);
}

