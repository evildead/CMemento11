/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "ui/cmementomainwindow.h"
#include <QApplication>
#include "model/cundoableinventorymanager.h"
#include "model/clistablefactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(APP_VERSION);

    /*
    CUndoableInventoryManager myInventoryManager;
    myInventoryManager.inventoryAddListable(CListableFactory::BOOK, "Midsummer Night's Dream");
    myInventoryManager.inventoryAddListable(CListableFactory::CDROM, "Rising Force");
    myInventoryManager.inventoryAddListable(CListableFactory::DVD, "The Green Mile");
    myInventoryManager.undoableInventory().printInventory();
    myInventoryManager.undoLastInventoryAction();
    myInventoryManager.undoableInventory().printInventory();
    myInventoryManager.inventoryAddListable(CListableFactory::DVD, "The Legend Of The Pianist on the Ocean");
    myInventoryManager.undoableInventory().printInventory();
    myInventoryManager.redoLastInventoryAction();
    myInventoryManager.undoableInventory().printInventory();
    myInventoryManager.inventoryInsertListable(CListableFactory::CDROM, "Eclipse", 1);
    myInventoryManager.inventoryInsertListable(CListableFactory::CDROM, "Magnum Opus", 2);
    myInventoryManager.undoableInventory().printInventory();
    myInventoryManager.undoLastInventoryAction();
    myInventoryManager.undoableInventory().printInventory();
    myInventoryManager.redoLastInventoryAction();
    myInventoryManager.undoableInventory().printInventory();
    */

    CMementoMainWindow w;
    w.show();

    return a.exec();
}
