#pragma once

#include <QObject>

enum AccountRole { Display = Qt::DisplayRole, User = Qt::UserRole, GetResource };

enum AccountTypes { ROOT, FOLDER, ACCOUNT };

enum AccountColumns { Resource, ColumnCount };

struct Account {
  public:
    int isAkk        = AccountTypes::FOLDER;
    QString resource = "";
    QString name     = "";
    QString password = "";
};
