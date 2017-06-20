/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CUNDOABLEINVENTORYMANAGER_H
#define CUNDOABLEINVENTORYMANAGER_H

#include <functional>
#include "cundoableinventory.h"

class CUndoableInventoryManager
{
protected:
    CUndoableInventory undoableInventory_;

public:
    CUndoableInventoryManager();
    virtual ~CUndoableInventoryManager();

protected:
    void executeNonUndoableMethod(function<void(const CUndoableInventory&)> method);
    void executeUndoableMethod(function<void(const CUndoableInventory&)> method);

public:
    const CUndoableInventory& undoableInventory() const;
    void setUndoableInventory(unique_ptr<CUndoableInventory> undoableInventory);

    int getInventorySize() const;

    const CListable* getInventoryListable(size_t pos) const;
    CListable* getInventoryListablePtr(size_t pos);

    bool isLastInventoryActionUndoable();
    bool isLastInventoryActionRedoable();
    void undoLastInventoryAction();
    void redoLastInventoryAction();

    void inventoryAddListable(CListableFactory::listable_t listableType, const std::string& name);
    void inventoryInsertListable(CListableFactory::listable_t listableType, const std::string& name, size_t pos);
    void inventoryRemoveListable(size_t pos);
    void inventoryClear();
};

#endif // CUNDOABLEINVENTORYMANAGER_H
