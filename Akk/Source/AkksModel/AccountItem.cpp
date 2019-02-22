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

void AccountItem::removeChild(int row) {
    m_childItems.removeAt(row);
}

void AccountItem::editChild(int row, const QString & res, const QString & acc,
                            const QString & pas) {
    auto item = m_childItems.at(row);
    item->setAcc(res, acc, pas);
}

void AccountItem::setAcc(const QString & res, const QString & acc, const QString & pas) {
    this->m_akk.resource = res;
    this->m_akk.name     = acc;
    this->m_akk.password = pas;
}

QList<Account> AccountItem::getAllAkks() {
    QList<Account> akks;
    for (auto & akk : m_childItems) {
        akks.append(akk->getAccount());
    }
    return akks;
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

QVariant AccountItem::data(int column, int role) const {
    if (role == AccountRole::Display || role == AccountRole::GetResource) {
        return m_akk.resource;
    } else if (role == AccountRole::GetAccountName) {
        return m_akk.name;
    } else if (role == AccountRole::GetPassword) {
        return m_akk.password;
    }
    return QVariant();
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

Account AccountItem::getAccount() {
    return this->m_akk;
}
