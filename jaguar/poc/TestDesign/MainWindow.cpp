/*
 * File:   MainWindow.cpp
 * Author: cross
 *
 * Created on January 12, 2010, 9:22 PM
 */

#include "MainWindow.h"
#include "Board.h"
#include <QHBoxLayout>
#include <QGraphicsPolygonItem>
#include <QPainterPath>

MainWindow::MainWindow() {
    widget.setupUi(this);

    Board* board = new Board();
    m_view = new QGraphicsView(board);

    QGraphicsItemGroup* group = new QGraphicsItemGroup();

    QGraphicsPolygonItem* item = new QGraphicsPolygonItem();
    QPainterPath path;
    path.moveTo(200, 50);
    path.arcTo(150, 0, 50, 50, 0, 90);
    path.arcTo(50, 0, 50, 50, 90, 90);
    path.arcTo(50, 50, 50, 50, 180, 90);
    path.arcTo(150, 50, 50, 50, 270, 90);
    path.lineTo(200, 25);
    QPolygonF myPolygon = path.toFillPolygon();

    item->setPolygon(myPolygon);
    QLinearGradient linearGradient(0, 0, 150, 150);
    linearGradient.setColorAt(0.0, Qt::white);
    QColor medium(200, 255, 200);
    linearGradient.setColorAt(0.3, medium);
    QColor dark(180, 220, 180);
    linearGradient.setColorAt(1.0, dark);
    item->setBrush(linearGradient);
    group->addToGroup(item);
    group->setFlag(QGraphicsItem::ItemIsMovable);
    group->setFlag(QGraphicsItem::ItemIsFocusable);
    group->setFlag(QGraphicsItem::ItemIsSelectable);

    QGraphicsPixmapItem* pixMap = new QGraphicsPixmapItem();
    board->addItem(group);
    connect(board, SIGNAL())
    widget.horizontalLayout->addWidget(m_view);
}

MainWindow::~MainWindow() {
}
