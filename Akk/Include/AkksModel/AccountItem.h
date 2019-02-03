#pragma once

#include "Include/structs.h"

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

    AccountItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    AccountItem * parent();
};
