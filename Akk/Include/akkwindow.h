#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>
#include <memory>

class AccountModel;
class AccountView;
class AccountProxy;
class Coder;
class DialogAddEdit;

class AkkWindow : public QMainWindow {
    Q_OBJECT

  public:
    AkkWindow(QWidget * parent = nullptr);
    ~AkkWindow();

  private:
    QSettings * settings;

    QString key;
    Coder * cod;

    std::shared_ptr<AccountModel> model;
    std::shared_ptr<AccountView> view;
    AccountProxy * proxy;

    DialogAddEdit * dialog;

    QLineEdit * passwordLine;
    QAction * loadAction;
    QAction * languageAction;
    QString curLang;
    QLabel * restartWarning;
    QLabel * restartWarningIcon;
    QString openedFile;

    QLineEdit * searchLine;

    QLabel * resValLabel;
    QLabel * logValLabel;
    QLabel * pasValLabel;

    QPushButton * addButton;
    QPushButton * editButton;
    QPushButton * delButton;
    QPushButton * saveButton;
    QPushButton * saveAsButton;

    void initAccModel();
    void initConnections();
    QLayout * initMainLayout();
    QToolBar * initToolbar();
    void successSave(const QString & file);
    bool isSaved;
    void Error(int x);

  protected:
    void keyPressEvent(QKeyEvent * ev) override;

  private slots:
    void currentItemValues(const QString & res, const QString & acc, const QString & pas);
    void PassTextChanged(const QString & str);
    void LoadClicked();
    void LanguageClicked();
    void addClicked();
    void addAccount(const QString & res, const QString & acc, const QString & pas);
    void editClicked();
    void editAccount(const QString & res, const QString & acc, const QString & pas);
    void delClicked();
    void saveClicked();
    void saveAsClicked();
};
