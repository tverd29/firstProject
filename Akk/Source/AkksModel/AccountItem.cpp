#include "Source/AkksModel/AccountItem.h"

#include "QVariant"

AccountItem::AccountItem(const Account & akk, AccountItem * parentItem)
    : m_akk(akk), m_parentItem(parentItem) {
}

AccountItem::AccountItem(const int type, AccountItem * parentItem) : m_parentItem(parentItem) {
    Account akk;
    akk.type = type;
    m_akk    = akk;
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

QList<AccountItem *> AccountItem::getChildrens() {
    return this->m_childItems;
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
    switch (role) {
        case AccountRole::Display:
            if (m_akk.type == AccountTypes::ACCOUNT_CHILD) {
                return this->row();
            } else if (m_akk.type == AccountTypes::PASSWORD_CHILD) {
                return this->row();
            }
            return m_akk.resource;
        case AccountRole::GetResource:
            if (m_akk.type == AccountTypes::ACCOUNT_CHILD) {
                return m_parentItem->data(AccountColumns::Resource, AccountRole::GetAccountName);
            } else if (m_akk.type == AccountTypes::PASSWORD_CHILD) {
                return m_parentItem->data(AccountColumns::Resource, AccountRole::GetPassword);
            }
            return m_akk.resource;
        case AccountRole::GetAccountName:
            return m_akk.name;
        case AccountRole::GetPassword:
            return m_akk.password;
        case AccountRole::GetType:
            return m_akk.type;
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

bool AccountItem::isSelected() {
    return this->selected;
}

void AccountItem::setSelected(bool value) {
    this->selected = value;
}
