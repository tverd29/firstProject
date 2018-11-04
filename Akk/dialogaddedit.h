#ifndef DIALOGADDEDIT_H
#define DIALOGADDEDIT_H

#include "account.h"
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class dialogAddEdit : public QDialog {
  Q_OBJECT
public:
  dialogAddEdit(QDialog *p);
  void setLines(QString res, QString akk, QString pass, QString str);
  QPushButton *ok;
  Account getAkk(bool editPushed);

private:
  QObject *parent;

  QLabel *resourceLabel;
  QLineEdit *resourceLine;
  QLabel *loginLabel;
  QLineEdit *loginLine;
  QLabel *passwordLabel;
  QLineEdit *passwordLine;

  QPushButton *no;
public slots:
  void resourceChanged(QString str);
  void loginChanged(QString str);
  void passwordChanged(QString str);
  void noClicked();
};

#endif // DIALOGADDEDIT_H
