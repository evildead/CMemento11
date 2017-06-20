/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CINVENTORYMODEL_H
#define CINVENTORYMODEL_H

#include <QAbstractListModel>
#include "cundoableinventorymanager.h"

class CInventoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CommandRoles {
        TitleRole = Qt::UserRole + 1
    };

    explicit CInventoryModel(CUndoableInventoryManager* inventoryManager, QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void addListable(int listableType, const QString& name);
    Q_INVOKABLE void insertListable(int listableType, const QString& name, int sourceRow);
    Q_INVOKABLE void removeListable(int sourceRow);
    Q_INVOKABLE bool isUndoable();
    Q_INVOKABLE bool isRedoable();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    Q_INVOKABLE void clearAll();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    CUndoableInventoryManager* myInventoryManager_;

signals:
    void modelModified();
};

#endif // CINVENTORYMODEL_H
