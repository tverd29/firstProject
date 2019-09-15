#pragma once

#include <QObject>

enum AccountRole {
    Display = Qt::DisplayRole,
    User    = Qt::UserRole,
    GetResource,
    GetAccountName,
    GetPassword
};

enum AccountTypes { ROOT, FOLDER, ACCOUNT, ACCOUNT_CHILD, PASSWORD_CHILD };

enum AccountColumns { Resource, ColumnCount };

struct Account {
  public:
    int isAkk        = AccountTypes::FOLDER;
    QString resource = "";
    QString name     = "";
    QString password = "";
};
