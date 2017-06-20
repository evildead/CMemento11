/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CMEMENTOMAINWINDOW_H
#define CMEMENTOMAINWINDOW_H

#include <QMainWindow>
#include "model/cinventorymodel.h"

namespace Ui {
class CMementoMainWindow;
}

class CMementoMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMementoMainWindow(QWidget *parent = 0);
    ~CMementoMainWindow();

private:
    Ui::CMementoMainWindow *ui;

protected:
    CInventoryModel *inventoryModel_;
    CUndoableInventoryManager inventoryManager_;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *) Q_DECL_OVERRIDE;
};

#endif // CMEMENTOMAINWINDOW_H
