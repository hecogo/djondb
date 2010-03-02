/*
 * File:   MainWindow.cpp
 * Author: cross
 *
 * Created on January 29, 2010, 3:11 PM
 */

#include "MainWindow.h"
#include "ui/CurrentDateTime.h"
#include "ui/MenuItem.h"
#include "jaguarui.h"
#include <QStandardItemModel>
#include <vector>

extern void registerClient();

MainWindow::MainWindow() {
    widget.setupUi(this);

    CurrentDateTime* time = new CurrentDateTime();
    //time->setLayoutDirection(Qt::RightToLeft);
//    widget.statusBarLayout->addWidget(time);
    widget.statusbar->addPermanentWidget(time);
    time->setVisible(true);
    time->start(1000);

    registerClient();
    
    init();
}

MainWindow::~MainWindow() {
}

void MainWindow::init() {
    QStandardItemModel* model = new QStandardItemModel();
    std::vector<MenuItem*> items = getMenuItems();
    for (std::vector<MenuItem*>::iterator iter = items.begin(); iter != items.end(); iter++) {
        model->appendRow(*iter);
    }
    /*
    MenuItem* item = new MenuItem("Administracion Demandas", 1);
    model->appendRow(item);
    MenuItem* sub1 = new MenuItem("Radicar demanda", 2);
    item->appendRow(sub1);
    item->appendRow(new MenuItem("Consultar demandas", 3));

    MenuItem* clientes = new MenuItem("Clientes", 4);
    model->appendRow(clientes);
    clientes->appendRow(new MenuItem("Crear Cliente", 5));
*/
    widget.treeView->setModel(model);

    connect(widget.treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClicked(QModelIndex)));
    qDebug("test");
}

void MainWindow::createClient() {
//    CrearClientes* clientes = new CrearClientes();
//    widget.mdiArea->addSubWindow(clientes, Qt::SubWindow);
//    clientes->show();
}

void MainWindow::doubleClicked(const QModelIndex &index) {
    QStandardItemModel* model = (QStandardItemModel*)widget.treeView->model();
    MenuItem* item = (MenuItem*)model->itemFromIndex(index);

    int id = item->value();
    ScreenBase* screen = callScreenFunction(id);
    widget.mdiArea->addSubWindow(screen, Qt::SubWindow);
    screen->show();
    qDebug("selected %s, value: %d", item->text().toStdString().c_str(), item->value());
}