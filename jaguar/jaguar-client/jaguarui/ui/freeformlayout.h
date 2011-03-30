/*
 * File:   freeformlayout.h
 * Author: cross
 *
 * Created on March 2, 2010, 4:21 PM
 */

#ifndef _FREEFORMLAYOUT_H
#define	_FREEFORMLAYOUT_H

#include <QStyle>
#include <QLayout>
#include <QWidget>
#include <Qt/qlist.h>

class FreeFormLayout : public QLayout {
public:
    FreeFormLayout(QWidget *parent = 0);
    ~FreeFormLayout();

    void addItem(QWidget *);
    void addItem(QLayoutItem *);
    QLayoutItem *itemAt(int index) const;
    QLayoutItem *takeAt(int index);
    int count() const;

    QSize sizeHint() const;
    QSize minimumSize() const;
    QSize maximumSize() const;
    Qt::Orientations expandingDirections() const;
    void setGeometry(const QRect&);
    QRect geometry() const;
    bool isEmpty() const;

    void addRow(QString label, QWidget* item);

private:
    int doLayout(const QRect &rect) const;

    struct ItemWrapper {
        QLayoutItem *m_item;
        bool m_endLine;
    public:

        ItemWrapper(QLayoutItem * i) {
            m_item = i;
        }

        ItemWrapper(QLayoutItem *i, bool endLine) {
            m_item = i;
            m_endLine = endLine;
        }
    };

    QList<ItemWrapper *> itemList;
    int maxcol;
};
#endif	/* _FREEFORMLAYOUT_H */

