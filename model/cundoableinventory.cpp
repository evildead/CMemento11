/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "cundoableinventory.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  CUndoableInventory  ///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CUndoableInventory::CUndoableInventory()
{
    inventory_ = new vector< shared_ptr<CListable> >();
}

CUndoableInventory::CUndoableInventory(const CUndoableInventory& other)
{
    inventory_ = 0;
    swap(other);
}

CUndoableInventory::~CUndoableInventory()
{
    if(inventory_ != 0) {
        delete inventory_;
    }
}

CUndoableInventory & CUndoableInventory::operator= (const CUndoableInventory& other)
{
    if(this != &other) {
        swap(other);
    }

    return *this;
}

void CUndoableInventory::swap(const CUndoableInventory& other)
{
    if(this->inventory_ != 0) {
        delete this->inventory_;
    }

    this->inventory_ = other.duplicateInventory();
}

vector< shared_ptr<CListable> > *CUndoableInventory::duplicateInventory() const
{
    if(this->inventory_ == 0) {
        return 0;
    }

    vector< shared_ptr<CListable> >* inventoryClone = new vector< shared_ptr<CListable> >();
    for(auto const& cmd: *inventory_) {
        CListable* pointer = cmd.get();
        inventoryClone->push_back( move(pointer->clone()) );
    }

    return inventoryClone;
}

int CUndoableInventory::getInventorySize() const
{
    return static_cast<int>(inventory_->size());
}

const CListable* CUndoableInventory::getListable(size_t pos) const
{
    if(this->inventory_ == 0) {
        return nullptr;
    }

    if(pos >= inventory_->size()) {
        return nullptr;
    }

    auto const& listable = (*inventory_)[pos];
    return listable.get();
}

CListable* CUndoableInventory::getListablePtr(size_t pos)
{
    if(this->inventory_ == 0) {
        return nullptr;
    }

    if(pos >= inventory_->size()) {
        return nullptr;
    }

    auto & listable = (*inventory_)[pos];
    return listable.get();
}

void CUndoableInventory::addListable(CListableFactory::listable_t listableType, const std::string& name)
{
    if(this->inventory_ == 0) {
        return;
    }

    // create the listable by using CListableFactory
    unique_ptr<CListable> listablePtr = CListableFactory::createListable(listableType, name);

    // add the listable to the inventory
    addListablePtr(move(listablePtr));
}

bool CUndoableInventory::insertListable(CListableFactory::listable_t listableType, const std::string& name, size_t pos)
{
    if(this->inventory_ == 0) {
        return false;
    }

    // create the listable by using CListableFactory
    unique_ptr<CListable> listablePtr = CListableFactory::createListable(listableType, name);

    // add the listable to the inventory
    return insertListablePtr(move(listablePtr), pos);
}

void CUndoableInventory::addListablePtr(shared_ptr<CListable> listablePtr)
{
    if(this->inventory_ == 0) {
        return;
    }

    inventory_->push_back(move(listablePtr));
}

bool CUndoableInventory::insertListablePtr(shared_ptr<CListable> listablePtr, size_t pos)
{
    if(this->inventory_ == 0) {
        return false;
    }

    if(pos >= inventory_->size()) {
        inventory_->push_back(move(listablePtr));
    }
    else {
        inventory_->insert(inventory_->begin() + pos, move(listablePtr));
    }

    return true;
}

bool CUndoableInventory::removeListable(size_t pos)
{
    if(this->inventory_ == 0) {
        return false;
    }

    if(pos >= inventory_->size()) {
        return false;
    }

    inventory_->erase(inventory_->begin() + pos);

    return true;
}

bool CUndoableInventory::clearAll()
{
    if(this->inventory_ == 0) {
        return false;
    }

    inventory_->clear();
    return true;
}

void CUndoableInventory::printInventory() const
{
    if(inventory_->size() > 0) {
        std::cout << std::endl << "Inventory contents:" << std::endl;
        for(unsigned int i = 0; i < inventory_->size(); i++) {
            auto const& listable = (*inventory_)[i];
            std::cout << listable.get()->getTitle() << std::endl;
        }
    }
    else {
        std::cout << "Inventory is empty!" << std::endl;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  CUndoableInventoryMemento  ////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CUndoableInventoryMemento::CUndoableInventoryMemento(const CUndoableInventory& obj): object_(obj)
{

}

// want a snapshot of CUndoableInventory itself because of its many data members
CUndoableInventory CUndoableInventoryMemento::snapshot() const
{
    return object_;
}

CUndoableInventoryMemento* CUndoableInventory::createMemento() const
{
    return new CUndoableInventoryMemento(*this);
}

void CUndoableInventory::reinstateMemento (CUndoableInventoryMemento* mem)
{
    *this = mem->snapshot();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  CUndoableInventoryAction  /////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<CUndoableInventoryAction*> CUndoableInventoryAction::commandList_(0);

std::vector<CUndoableInventoryMemento*> CUndoableInventoryAction::mementoList_(0);

int CUndoableInventoryAction::numCommands_ = 0;

int CUndoableInventoryAction::maxCommands_ = -1;

CUndoableInventoryAction::CUndoableInventoryAction(CUndoableInventory *newReceiver, function<void(const CUndoableInventory&)> newReceiverAction) :
    receiver_(newReceiver), receiverAction_(newReceiverAction)
{

}

CUndoableInventoryAction::~CUndoableInventoryAction()
{

}

void CUndoableInventoryAction::execute()
{
    if(mementoList_.size() < numCommands_ + 1) {
        mementoList_.resize (numCommands_ + 1);
    }

    mementoList_[numCommands_] = receiver_->createMemento();  // saves the last value

    if(commandList_.size() < numCommands_ + 1) {
        commandList_.resize (numCommands_ + 1);
    }

    commandList_[numCommands_] = this;  // saves the last command

    if(numCommands_ > maxCommands_) {
        maxCommands_ = numCommands_;
    }

    numCommands_++;

    receiverAction_(*receiver_);
}

bool CUndoableInventoryAction::isUndoable()
{
    if(numCommands_ == 0) {
        return false;
    }
    else {
        return true;
    }
}

bool CUndoableInventoryAction::isRedoable()
{
    if (numCommands_ > maxCommands_) {
        return false;
    }
    else {
        return true;
    }
}

void CUndoableInventoryAction::undo()
{
    if(numCommands_ == 0) {
        std::cout << "There is nothing to undo at this point." << std::endl;
        return;
    }
    commandList_[numCommands_ - 1]->receiver_->reinstateMemento(mementoList_[numCommands_ - 1]);
    numCommands_--;
}

void CUndoableInventoryAction::redo()
{
    if (numCommands_ > maxCommands_) {
        std::cout << "There is nothing to redo at this point." << std::endl;
        return;
    }
    CUndoableInventoryAction* commandRedo = commandList_[numCommands_];
    commandRedo->receiverAction_(*(commandRedo->receiver_));
    numCommands_++;
}

void CUndoableInventoryAction::clearAll()
{
    for(CUndoableInventoryAction* tmTechCare : commandList_) {
        delete tmTechCare;
    }

    for(CUndoableInventoryMemento* tmTechMemento : mementoList_) {
        delete tmTechMemento;
    }

    numCommands_ = 0;
    maxCommands_ = -1;

    commandList_.resize(0);
    mementoList_.resize(0);
}
