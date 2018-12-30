#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "account.h"

class DialogAddEdit : public QDialog {
    Q_OBJECT
  public:
    DialogAddEdit(QDialog * p);
    void setLines(QString res, QString akk, QString pass, QString str);
    QPushButton * ok;
    Account getAkk(bool editPushed);

  private:
    QLabel * resourceLabel;
    QLineEdit * resourceLine;
    QLabel * loginLabel;
    QLineEdit * loginLine;
    QLabel * passwordLabel;
    QLineEdit * passwordLine;

    QPushButton * no;
  public slots:
    void resourceChanged(QString str);
    void loginChanged(QString str);
    void passwordChanged(QString str);
    void noClicked();
};
