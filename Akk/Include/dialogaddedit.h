#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class DialogAddEdit : public QDialog {
    Q_OBJECT
  public:
    DialogAddEdit(QWidget * p);
    void setLines(const QString & str = "button", const QString res = QString(),
                  const QString & akk = QString(), const QString & pas = QString());

  private:
    QLabel * resourceLabel;
    QLineEdit * resourceLine;
    QLabel * loginLabel;
    QLineEdit * loginLine;
    QLabel * passwordLabel;
    QLineEdit * passwordLine;

    QPushButton * no;
    QPushButton * ok;

    bool isAdding = false;
  public slots:
    void resourceChanged(QString str);
    void loginChanged(QString str);
    void passwordChanged(QString str);
    void noClicked();
    void okClicked();

  signals:
    void addAccount(const QString & res, const QString & acc, const QString & pas);
    void editAccount(const QString & res, const QString & acc, const QString & pas);
};
