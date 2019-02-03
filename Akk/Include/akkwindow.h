#pragma once

#include <QDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
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

    //    QList<Account> akks;

    DialogAddEdit * dialog;

    QLineEdit * passwordLine;
    QString openedFile;
    QPushButton * loadButton;

    QLineEdit * searchLine;

    QLabel * resValLabel;
    QLabel * logValLabel;
    QLabel * pasValLabel;
    //    QListWidget * result;
    //    QListView * result;

    QPushButton * addButton;
    QPushButton * editButton;
    QPushButton * delButton;
    QPushButton * saveButton;
    QPushButton * saveAsButton;

    void successSave(QString file);

    bool addPushed;
    bool editPushed;
    bool isSaved;

    void refreshResult();

    //*******try AES*************
    //    QLineEdit * encryptLine;
    //    QLineEdit * decryptLine;
    //    QPushButton * encryptButton;
    //    QPushButton * decryptButton;
    //***************************
  private slots:
    void currentItemValues(int curRow);
    void listDoubleClicked(const QModelIndex & index);
    void PassTextChanged(QString str);
    void SearchTextChanged(QString str);
    void LoadClicked();
    void addClicked();
    void editClicked();
    void delClicked();
    void saveClicked();
    void saveAsClicked();
    void addToAkks();
    //*******try AES*************
    //    void encryptClicked();
    //    void decryptClicked();
    //***************************
};
