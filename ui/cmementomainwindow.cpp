/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "cmementomainwindow.h"
#include "ui_cmementomainwindow.h"
#include <QtQml/QQmlContext>

CMementoMainWindow::CMementoMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMementoMainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("Undoable Inventory - %1").arg(qApp->applicationVersion()));

    inventoryModel_ = new CInventoryModel(&inventoryManager_);

    QQmlContext *ctxt = ui->inventoryQuickWidget->rootContext();
    // assign our custom inventoryModel_
    ctxt->setContextProperty("inventoryModel", inventoryModel_);
    // assign qml/inventoryView.qml to inventoryQuickWidget
    ui->inventoryQuickWidget->setSource(QUrl("qrc:/qml/inventoryView.qml"));
}

CMementoMainWindow::~CMementoMainWindow()
{
    delete ui;
    delete inventoryModel_;
}

void CMementoMainWindow::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    qApp->quit();
}

void CMementoMainWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
}
