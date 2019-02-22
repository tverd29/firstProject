#pragma once

#include <QDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
#include <memory>

#include "Include/AkksModel/AccountModel.h"
#include "Include/AkksModel/AccountView.h"
#include "coder.h"
#include "dialogaddedit.h"

class AkkWindow : public QDialog {
    Q_OBJECT

  public:
    AkkWindow(QWidget * parent = nullptr);
    ~AkkWindow();

  private:
    QString key;
    Coder * cod;

    std::shared_ptr<AccountModel> model;
    std::shared_ptr<AccountView> view;
    QSortFilterProxyModel * proxy;

    DialogAddEdit * dialog;

    QLineEdit * passwordLine;
    QString openedFile;
    QPushButton * loadButton;

    QLineEdit * searchLine;

    QLabel * resValLabel;
    QLabel * logValLabel;
    QLabel * pasValLabel;

    QPushButton * addButton;
    QPushButton * editButton;
    QPushButton * delButton;
    QPushButton * saveButton;
    QPushButton * saveAsButton;

    void successSave(QString file);

    bool isSaved;

  protected:
    void keyPressEvent(QKeyEvent * ev) override;

  private slots:
    void currentItemValues(const QString & res, const QString & acc, const QString & pas);
    void PassTextChanged(QString str);
    void SearchTextChanged(QString str);
    void LoadClicked();
    void addClicked();
    void addAccount(const QString & res, const QString & acc, const QString & pas);
    void editClicked();
    void editAccount(const QString & res, const QString & acc, const QString & pas);
    void delClicked();
    void saveClicked();
    void saveAsClicked();
};
