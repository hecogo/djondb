/* 
 * File:   ScreenBase.cpp
 * Author: cross
 * 
 * Created on February 24, 2010, 10:14 PM
 */

#include <qt4/QtGui/qwidget.h>

#include "ScreenBase.h"
#include <QVBoxLayout>
#include <QAction>

ScreenBase::ScreenBase(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f) {
    m_formLayout = new FreeFormLayout();
    QVBoxLayout* vertical = new QVBoxLayout();
    m_toolBar = new QToolBar();
    
    vertical->addWidget(m_toolBar);
    vertical->addLayout(m_formLayout);
    setLayout(vertical);
}

ScreenBase::~ScreenBase() {
    delete(m_formLayout);
    delete(m_toolBar);
}

void ScreenBase::addAction(QString action, const char *slot) {
    QAction* qaction = m_toolBar->addAction(action);
    connect(qaction, SIGNAL(triggered()), this, slot);
}

void ScreenBase::addRow(QString label, QWidget* widget) {
    m_formLayout->addRow(label, widget);
}

