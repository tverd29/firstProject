#pragma once

#include "Source/structs.h"

class AccountItem {
  private:
    Account m_akk;
    QString id;
    AccountItem * m_parentItem;
    QList<AccountItem *> m_childItems;
    bool selected = false;

  public:
    explicit AccountItem(const Account & akk, AccountItem * parentItem = nullptr);
    explicit AccountItem(const int type, AccountItem * parentItem = nullptr);
    ~AccountItem();

    void appendChild(AccountItem * child);
    void removeChild(int row);
    void editChild(int row, const QString & res, const QString & acc, const QString & pas);
    void setAcc(const QString & res, const QString & acc, const QString & pas);
    QList<Account> getAllAkks();
    QList<AccountItem *> getChildrens();
    AccountItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int role = AccountRole::Display) const;
    int row() const;
    AccountItem * parent();
    Account getAccount();

    const QString getId();

    bool isSelected();
    void setSelected(bool value);

    bool isResourceValid(const QString & res);
};
