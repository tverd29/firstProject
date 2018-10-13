#include "account.h"

Account::Account(const QString &myResource, const QString &myName,
                 const QString &myPassword) {

  resource = myResource;
  name = myName;
  password = myPassword;
}

void Account::setValues(const QString &myResource, const QString &myName,
                        const QString &myPassword) {
  resource = myResource;
  name = myName;
  password = myPassword;
}

QString Account::getResource() const { return resource; }

QString Account::getName() const { return name; }

QString Account::getPassword() const { return password; }
