## CMemento11

It is an application to show the use of [Memento](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Memento) and [Command](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Command) design patterns, to implement a undo/redo listView in Qt/C++/QML.

The data model is represented by two classes: `CUndoableInventory` and `CListable`

_CUndoableInventory_ class represents the listView and contains a vector of objects extending CListable interface.
```cpp
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
```

_CListable_ is a pure virtual class representing an object contained in the listView.
```cpp
// Abstract class CListable
class CListable
{
public:
    virtual std::string getTitle() const {
        std::string title = getType();
        title.append(" - ").append(getName());

        return title;
    }

    virtual std::unique_ptr<CListable> clone() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string toString() const = 0;
};
```

This design decouples the _CListable_ abstraction from its implementation (in this case: _CBook_, _CCdRom_, _CDvd_), so that the two can vary independently: it complies to the [Bridge](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#2._Bridge) Design Pattern.


### Undo/Redo: _Command_ and _Memento_ patterns.

_Command_ pattern is an _Object behavioral pattern_ that decouples sender and receiver by encapsulating a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and above all support undo-able operations.
It can also be thought as an object oriented equivalent of _call-back_ method.

Without violating encapsulation the _Memento_ pattern will capture and externalize an object’s internal state so that the object can be restored to this state later.
The _Originator_ (the object to be saved) creates a snap-shot of itself as a _Memento_ object, and passes that reference to the _Caretaker_ object. The _Caretaker_ object keeps the _Memento_ until such a time as the _Originator_ may want to revert to a previous state as recorded in the _Memento_ object.

In my implementation the _originator_ is represented by _CUndoableInventory_.
_CUndoableInventory_ creates a snap-shot of itself as a _CUndoableInventoryMemento_ object by invoking createMemento(), and can revert to a previous state by invoking reinstateMemento `(CUndoableInventoryMemento* mem)`:
```cpp
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
```

The _Caretaker_ is represented by _CUndoableInventoryAction_ class (_Command_ pattern, where the receiver is _CUndoableInventory_):
```cpp
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
    CUndoableInventoryAction(CUndoableInventory *newReceiver,
                             function<void(const CUndoableInventory&)> newReceiverAction);
    virtual ~CUndoableInventoryAction();

    virtual void execute();

    static bool isUndoable();
    static bool isRedoable();
    static void undo();
    static void redo();
    static void clearAll();
};

#endif // CUNDOABLEINVENTORY_H
```

An instance of this class represents an undoable operation performed on the _CUndoableInventory_ object:
it keeps a pointer to an instance of the receiver (_CUndoableInventory_) and the method to be performed on the receiver as a `function<void(const CUndoableInventory&)>`  (the [std::function](http://en.cppreference.com/w/cpp/utility/functional/function) encapsulates both the method of class _CUndoableInventory_ and the parameters to be passed to it).

Moreover, the _CUndoableInventoryAction_ class is the _Caretaker_, because it keeps two static lists:
  - 1) the list of actions performed;
  - 2) the list of the inner states of the undoable inventory (_CUndoableInventoryMemento_ object).

The **undo/redo** functions have been implemented as follows:
```cpp
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
```


### Undoable Operations

The class in charge of performing undoable operations on a _CUndoableInventory_ object, is _CUndoableInventoryManager_:
```cpp
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
```

The magic happens inside `executeUndoableMethod`
```cpp
void CUndoableInventoryManager::executeUndoableMethod(function<void(const CUndoableInventory&)> method)
{
    CUndoableInventoryAction* myInventoryAction = new CUndoableInventoryAction(&undoableInventory_, method);
    myInventoryAction->execute();
}
```
which receives a `function<void(const CUndoableInventory&)>` as parameter, which encapsulates the method of _CUndoableInventory_ to be invoked and the parameters.
This method creates an action (_Command_ pattern) by creating an object of type _CUndoableInventoryAction_, and then invokes its execute method `myInventoryAction->execute();`.

In this way, any function willing to be _undoable_, will just have to wrap the _CUndoableInventory_ method and the parameters, inside a _std::function_

For example, let's have a look at `inventoryAddListable(CListableFactory::listable_t listableType, const std::string& name)`:
```cpp
void CUndoableInventoryManager::inventoryAddListable(CListableFactory::listable_t listableType, const string &name)
{
    std::function<void(const CUndoableInventory&)> inventoryMethod = std::bind(&CUndoableInventory::addListable, &undoableInventory_, listableType, name);
    executeUndoableMethod(inventoryMethod);
}
```

### C++ <-----> QML
In order to "bind" the [QML undoable listView](https://github.com/evildead/CMemento11/blob/master/qml/inventoryView.qml) with the data model represented by _CUndoableInventoryManager_ object, I set up a MVC architecture.
 - Model: _CUndoableInventoryManager_
 - View: _QML undoable listView_
 - Controller: an object of type _CInventoryModel_ extending _QAbstractListModel_

The class _CInventoryModel_ receives commands from _Javascript_ functions used in QML undoable listView, and then it performs modifications on the _data model_ and the _listView_ itself.
For example, let's have a look at the `addListable` method:
```cpp
/**
 * C++
 */
void CInventoryModel::addListable(int listableType, const QString& name)
{
    CListableFactory::listable_t listableFactoryType = static_cast<CListableFactory::listable_t>(listableType);
    beginInsertRows(QModelIndex(), myInventoryManager_->getInventorySize(), myInventoryManager_->getInventorySize());
    myInventoryManager_->inventoryAddListable(listableFactoryType, name.toStdString());
    endInsertRows();
    emit modelModified();
}
```

```js
/**
 * QML/Javascript
 */
function execAddListable() {
	var listableType = listableTypeComboBox.currentIndex + 1;
	var listableName = listableNameTextField.text;
	inventoryModel.addListable(listableType, listableName);
	inventoryList.positionViewAtEnd();
}

...
    Button {
        x: 10
        y: 100
        id: cmdButtonAdd
        Layout.alignment: Qt.AlignLeft
        anchors.topMargin: 10

        text: qsTr("Add Item")

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: cmdButtonAdd.down ? selectedColor : normalColor
                border.width: 1
                radius: 2
            }

            label: Text {
                text: cmdButtonAdd.text
                opacity: enabled ? 1.0 : 0.3
                color: cmdButtonAdd.down ? selectedColor : normalColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        action: Action {
            enabled: true

            onTriggered: {
                execAddListable();
                console.log("Add detected!")
            }
        }
    }
...
```

In this way I was able to implement all of the methods to add, insert, delete items on the list, and the undo/redo actions.
