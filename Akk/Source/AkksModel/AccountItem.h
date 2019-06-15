#pragma once

#include "Source/structs.h"

class AccountItem {
  private:
    Account m_akk;
    AccountItem * m_parentItem;
    QList<AccountItem *> m_childItems;

  public:
    explicit AccountItem(const Account & akk, AccountItem * parentItem = nullptr);
    explicit AccountItem(const int type, AccountItem * parentItem = nullptr);
    ~AccountItem();

    void appendChild(AccountItem * child);
    void removeChild(int row);
    void editChild(int row, const QString & res, const QString & acc, const QString & pas);
    void setAcc(const QString & res, const QString & acc, const QString & pas);
    QList<Account> getAllAkks();

    AccountItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int role = AccountRole::Display) const;
    int row() const;
    AccountItem * parent();
    Account getAccount();
};
