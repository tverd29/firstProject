#pragma once

#include <QObject>

enum AccountRole {
    Display = Qt::DisplayRole,
    User    = Qt::UserRole,
    GetId,
    GetResource,
    GetAccountName,
    GetPassword,
    GetType,
    SetSelected,
    IsSelected,
    ClearSelection
};

enum AccountTypes { ROOT, ACCOUNT, ACCOUNT_CHILD, PASSWORD_CHILD };

enum AccountColumns { Resource, ColumnCount };

enum SettingsColumns { Alias, Values, ColumnsCount };

enum SettingsRows { DefaultFile, Language, RowsCount };

struct Account {
  public:
    int type         = AccountTypes::ACCOUNT;
    QString resource = "";
    QString name     = "";
    QString password = "";
};
