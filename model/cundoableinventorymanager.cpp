/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "cundoableinventorymanager.h"

CUndoableInventoryManager::CUndoableInventoryManager()
{

}

CUndoableInventoryManager::~CUndoableInventoryManager()
{
    // clear the CUndoableInventoryAction buffers for undo redo
    CUndoableInventoryAction::clearAll();
}

const CUndoableInventory& CUndoableInventoryManager::undoableInventory() const
{
    return undoableInventory_;
}

void CUndoableInventoryManager::setUndoableInventory(unique_ptr<CUndoableInventory> undoableInventory)
{
    CUndoableInventoryAction::clearAll();
    CUndoableInventory *myInventory = undoableInventory.get();
    undoableInventory_ = *myInventory;
}

int CUndoableInventoryManager::getInventorySize() const
{
    return undoableInventory_.getInventorySize();
}

const CListable* CUndoableInventoryManager::getInventoryListable(size_t pos) const
{
    return undoableInventory_.getListable(pos);
}

CListable* CUndoableInventoryManager::getInventoryListablePtr(size_t pos)
{
    return undoableInventory_.getListablePtr(pos);
}

void CUndoableInventoryManager::executeNonUndoableMethod(function<void(const CUndoableInventory&)> method)
{
    method(undoableInventory_);
}

void CUndoableInventoryManager::executeUndoableMethod(function<void(const CUndoableInventory&)> method)
{
    CUndoableInventoryAction* myInventoryAction = new CUndoableInventoryAction(&undoableInventory_, method);
    myInventoryAction->execute();
}

bool CUndoableInventoryManager::isLastInventoryActionUndoable()
{
    return CUndoableInventoryAction::isUndoable();
}

bool CUndoableInventoryManager::isLastInventoryActionRedoable()
{
    return CUndoableInventoryAction::isRedoable();
}

void CUndoableInventoryManager::undoLastInventoryAction()
{
    CUndoableInventoryAction::undo();
}

void CUndoableInventoryManager::redoLastInventoryAction()
{
    CUndoableInventoryAction::redo();
}

void CUndoableInventoryManager::inventoryAddListable(CListableFactory::listable_t listableType, const string &name)
{
    std::function<void(const CUndoableInventory&)> inventoryMethod = std::bind(&CUndoableInventory::addListable, &undoableInventory_, listableType, name);
    executeUndoableMethod(inventoryMethod);
}

void CUndoableInventoryManager::inventoryInsertListable(CListableFactory::listable_t listableType, const string &name, size_t pos)
{
    std::function<void(const CUndoableInventory&)> inventoryMethod = std::bind(&CUndoableInventory::insertListable, &undoableInventory_, listableType, name, pos);
    executeUndoableMethod(inventoryMethod);
}

void CUndoableInventoryManager::inventoryRemoveListable(size_t pos)
{
    std::function<void(const CUndoableInventory&)> inventoryMethod = std::bind(&CUndoableInventory::removeListable, &undoableInventory_, pos);
    executeUndoableMethod(inventoryMethod);
}

void CUndoableInventoryManager::inventoryClear()
{
    CUndoableInventoryAction::clearAll();
    undoableInventory_.clearAll();
}
