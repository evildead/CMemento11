/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CUNDOABLEINVENTORY_H
#define CUNDOABLEINVENTORY_H

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include "clistable.h"
#include "clistablefactory.h"

using namespace std;


class CUndoableInventoryMemento;

/**
 * @brief The CUndoableInventory class
 */
class CUndoableInventory
{
protected:
    // list of CListable
    vector< shared_ptr<CListable> > *inventory_;

    vector< shared_ptr<CListable> > *duplicateInventory() const;
    void swap(const CUndoableInventory& other);

public:
    CUndoableInventory();
    CUndoableInventory(const CUndoableInventory& other);
    virtual ~CUndoableInventory();

    CUndoableInventory & operator= (const CUndoableInventory& other);

    // number of listables in the list
    int getInventorySize() const;

    // get the listable at index 'pos' (unchangeable)
    const CListable* getListable(size_t pos) const;

    // get the listable at index 'pos' (changeable)
    CListable* getListablePtr(size_t pos);

    // command list modifiers
    void addListable(CListableFactory::listable_t listableType, const std::string& name);
    bool insertListable(CListableFactory::listable_t listableType, const std::string& name, size_t pos);
    bool removeListable(size_t pos);
    bool clearAll();

    // print to std::out
    void printInventory() const;

    // memento methods
    CUndoableInventoryMemento* createMemento() const;
    void reinstateMemento (CUndoableInventoryMemento* mem);

protected:
    void addListablePtr(shared_ptr<CListable> listablePtr);
    bool insertListablePtr(shared_ptr<CListable> listablePtr, size_t pos);
};


/**
 * @brief The CUndoableInventoryMemento class
 */
class CUndoableInventoryMemento
{
private:
    CUndoableInventory object_;

public:
    CUndoableInventoryMemento(const CUndoableInventory& obj);

    // want a snapshot of CUndoableInventory itself because of its many data members
    CUndoableInventory snapshot() const;
};


/**
 * @brief The CUndoableInventoryAction class
 */
class CUndoableInventoryAction
{
private:
    CUndoableInventory* receiver_;

    // this std::function will contain the reference to receiver's method and all the parameters
    function<void(const CUndoableInventory&)> receiverAction_;

    static std::vector<CUndoableInventoryAction*> commandList_;
    static std::vector<CUndoableInventoryMemento*> mementoList_;
    static int numCommands_;
    static int maxCommands_;

public:
    CUndoableInventoryAction(CUndoableInventory *newReceiver, function<void(const CUndoableInventory&)> newReceiverAction);
    virtual ~CUndoableInventoryAction();

    virtual void execute();

    static bool isUndoable();
    static bool isRedoable();
    static void undo();
    static void redo();
    static void clearAll();
};

#endif // CUNDOABLEINVENTORY_H
