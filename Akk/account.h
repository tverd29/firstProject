#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <QString>

class Account {

public:
  Account(const QString &res, const QString &myname, const QString &mypass);
  void setValues(const QString &myResource, const QString &myName,
                 const QString &myPassword);
  QString getResource() const;
  QString getName() const;
  QString getPassword() const;

private:
  QString resource;
  QString name;
  QString password;
};

#endif // ACCOUNTS_H
