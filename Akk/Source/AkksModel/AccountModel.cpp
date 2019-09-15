#include "Source/AkksModel/AccountModel.h"

#include <QColor>

#include "Source/AkksModel/AccountItem.h"

AccountModel::AccountModel(QObject * parent) : QAbstractItemModel(parent) {
    rootItem = new AccountItem(AccountTypes::ROOT);
}

AccountModel::~AccountModel() {
    delete rootItem;
}

QVariant AccountModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    AccountItem * item = static_cast<AccountItem *>(index.internalPointer());
    if (!item) {
        return QVariant();
    }

    switch (role) {
        case Qt::BackgroundRole:
            return QVariant(QColor("white"));
        case Qt::DisplayRole:
        case Qt::EditRole:
        case AccountRole::GetResource:
        case AccountRole::GetAccountName:
        case AccountRole::GetPassword:
        case AccountRole::GetType:
            return item->data(index.column(), role);
    }
    return QVariant();
}

Qt::ItemFlags AccountModel::flags(const QModelIndex & index) const {
    if (!index.isValid()) {
        return nullptr;
    }

    return QAbstractItemModel::flags(index);
}

QVariant AccountModel::headerData(int section, Qt::Orientation orientation, int role) const {
    return "Resource";
}

QModelIndex AccountModel::index(int row, int column, const QModelIndex & parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    AccountItem * parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<AccountItem *>(parent.internalPointer());

    AccountItem * childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex AccountModel::parent(const QModelIndex & index) const {
    if (!index.isValid())
        return QModelIndex();

    AccountItem * childItem  = static_cast<AccountItem *>(index.internalPointer());
    AccountItem * parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int AccountModel::rowCount(const QModelIndex & parent) const {
    AccountItem * parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<AccountItem *>(parent.internalPointer());

    return parentItem->childCount();
}

int AccountModel::columnCount(const QModelIndex & parent) const {
    if (parent.isValid())
        return static_cast<AccountItem *>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

void AccountModel::reloadModel(QList<Account> & akks) {
    this->beginResetModel();
    clearModel();

    for (auto & akk : akks) {
        AccountItem * item = new AccountItem(akk, rootItem);
        this->addItem(item);
    }
    this->endResetModel();
}

void AccountModel::insert(Account & akk) {
    this->beginInsertRows(QModelIndex(), rootItem->childCount(), rootItem->childCount());

    AccountItem * item = new AccountItem(akk, rootItem);
    this->addItem(item);

    this->endInsertRows();
}

void AccountModel::remove(const QModelIndex & index) {
    if (index.row() < this->rootItem->childCount()) {
        this->beginRemoveRows(QModelIndex(), index.row(), index.row());

        this->rootItem->removeChild(index.row());

        this->endRemoveRows();
    }
}

void AccountModel::edit(const QModelIndex & index, const QString & res, const QString & acc,
                        const QString & pas) {
    this->rootItem->editChild(index.row(), res, acc, pas);
    emit dataChanged(index, index);
}

QList<Account> AccountModel::getAllAkks() {
    return this->rootItem->getAllAkks();
}

int AccountModel::getRowCount() {
    return this->rootItem->childCount();
}

void AccountModel::clearModel() {
    this->rootItem->clear();
    rootItem = new AccountItem(AccountTypes::ROOT);
}

void AccountModel::addItem(AccountItem * item) {
    rootItem->appendChild(item);
    AccountItem * accItem  = new AccountItem(AccountTypes::ACCOUNT_CHILD, item);
    AccountItem * passItem = new AccountItem(AccountTypes::PASSWORD_CHILD, item);
    item->appendChild(accItem);
    item->appendChild(passItem);
}
