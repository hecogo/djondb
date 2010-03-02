/*
 * File:   CurrentDateTime.cpp
 * Author: cross
 *
 * Created on January 29, 2010, 4:32 PM
 */

#include "CurrentDateTime.h"
#include <QDateTime>

CurrentDateTime::CurrentDateTime() {
    widget.setupUi(this);
    m_timer = new QTimer();
    updateDateTime();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

CurrentDateTime::~CurrentDateTime() {
}

void CurrentDateTime::updateDateTime() {
    QDateTime now = QDateTime::currentDateTime();
    QString format("dd/MM/yy h:mm:ss ap");
    QString date = now.toString(format);
    widget.label->setText(date);
}

void CurrentDateTime::timeout() {
    updateDateTime();
}

void CurrentDateTime::start(int millisecs) {
    m_timer->start(millisecs);
}

void CurrentDateTime::stop() {
    m_timer->stop();
}
