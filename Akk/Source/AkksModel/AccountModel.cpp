#include "Include/AkksModel/AccountModel.h"

AccountModel::AccountModel(QObject * parent) : QAbstractItemModel(parent) {
    rootItem = new AccountItem(AccountTypes::ROOT);
}

AccountModel::~AccountModel() {
    delete rootItem;
}

QVariant AccountModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != AccountRole::Display)
        return QVariant();

    AccountItem * item = static_cast<AccountItem *>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags AccountModel::flags(const QModelIndex & index) const {
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant AccountModel::headerData(int section, Qt::Orientation orientation, int role) const {
    return QVariant();
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
        rootItem->appendChild(item);
    }
    this->endResetModel();
}

void AccountModel::clearModel() {
    rootItem = new AccountItem(AccountTypes::ROOT);
    this->m_akks.clear();
}
