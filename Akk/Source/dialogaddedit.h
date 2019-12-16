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
    DialogAddEdit(QWidget * p = nullptr);
    void setLines(const QString & str = "button", bool isAdding = false,
                  const QString res = QString(), const QString & akk = QString(),
                  const QString & pas = QString());
    void resourceValidAnswer(const QString & res, bool isValidRes = true);

  private:
    QLabel * resourceLabel;
    QLineEdit * resourceLine;
    QLabel * loginLabel;
    QLineEdit * loginLine;
    QLabel * passwordLabel;
    QLineEdit * passwordLine;

    QPushButton * no;
    QPushButton * ok;

    QString oldRes;
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
    void isResourceValid(const QString & res);
};
