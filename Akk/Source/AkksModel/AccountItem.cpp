#include "Include/AkksModel/AccountItem.h"

#include "QVariant"

AccountItem::AccountItem(const Account & akk, AccountItem * parentItem) {
    m_parentItem = parentItem;
    m_akk        = akk;
}

AccountItem::AccountItem(const int type, AccountItem * parentItem) {
    m_parentItem = parentItem;
    Account akk;
    switch (type) {
        case AccountTypes::ROOT: {
            akk.isAkk = type;
            break;
        }
        case AccountTypes::FOLDER: {
            akk.isAkk = type;
            break;
        }
    }
    m_akk = akk;
}

AccountItem::~AccountItem() {
    qDeleteAll(m_childItems);
}

void AccountItem::appendChild(AccountItem * child) {
    m_childItems.append(child);
}

AccountItem * AccountItem::child(int row) {
    return m_childItems.value(row);
}

int AccountItem::childCount() const {
    return m_childItems.count();
}

int AccountItem::columnCount() const {
    return AccountColumns::ColumnCount;
}

QVariant AccountItem::data(int column) const {
    return QVariant::fromValue(m_akk.resource);
}

int AccountItem::row() const {
    if (m_parentItem) {
        return m_parentItem->m_childItems.indexOf(const_cast<AccountItem *>(this));
    }
    return 0;
}

AccountItem * AccountItem::parent() {
    return m_parentItem;
}
