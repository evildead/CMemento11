/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "cinventorymodel.h"

CInventoryModel::CInventoryModel(CUndoableInventoryManager* inventoryManager, QObject *parent)
    : myInventoryManager_(inventoryManager), QAbstractListModel(parent)
{
}

QHash<int, QByteArray> CInventoryModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    return roles;
}

QVariant CInventoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

int CInventoryModel::rowCount(const QModelIndex &parent) const
{
    return myInventoryManager_->getInventorySize();
}

QVariant CInventoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= myInventoryManager_->getInventorySize()) {
        return QVariant();
    }

    const CListable* listable = myInventoryManager_->getInventoryListable(index.row());

    if (role == TitleRole) {
        return QString::fromStdString(listable->getTitle());
    }
    else if (role == Qt::ToolTipRole) {
        return QString::fromStdString(listable->toString());
    }

    return QVariant();
}

void CInventoryModel::addListable(int listableType, const QString& name)
{
    CListableFactory::listable_t listableFactoryType = static_cast<CListableFactory::listable_t>(listableType);
    beginInsertRows(QModelIndex(), myInventoryManager_->getInventorySize(), myInventoryManager_->getInventorySize());
    myInventoryManager_->inventoryAddListable(listableFactoryType, name.toStdString());
    endInsertRows();
    emit modelModified();
}

void CInventoryModel::insertListable(int listableType, const QString& name, int sourceRow)
{
    CListableFactory::listable_t listableFactoryType = static_cast<CListableFactory::listable_t>(listableType);
    beginInsertRows(QModelIndex(), sourceRow, sourceRow);
    myInventoryManager_->inventoryInsertListable(listableFactoryType, name.toStdString(), sourceRow);
    endInsertRows();
    emit modelModified();
}

void CInventoryModel::removeListable(int sourceRow)
{
    beginRemoveRows(QModelIndex(), sourceRow, sourceRow);
    myInventoryManager_->inventoryRemoveListable(sourceRow);
    endRemoveRows();
    emit modelModified();
}

bool CInventoryModel::isUndoable()
{
    return myInventoryManager_->isLastInventoryActionUndoable();
}

bool CInventoryModel::isRedoable()
{
    return myInventoryManager_->isLastInventoryActionRedoable();
}

void CInventoryModel::undo()
{
    beginResetModel();
    myInventoryManager_->undoLastInventoryAction();
    endResetModel();
    emit modelModified();
}

void CInventoryModel::redo()
{
    beginResetModel();
    myInventoryManager_->redoLastInventoryAction();
    endResetModel();
    emit modelModified();
}

void CInventoryModel::clearAll()
{
    beginResetModel();
    myInventoryManager_->inventoryClear();
    endResetModel();
    emit modelModified();
}
