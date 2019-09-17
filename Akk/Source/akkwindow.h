#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>
#include <memory>

class AccountItemDelegate;
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
    QSettings * settings = nullptr;

    QString key;
    Coder * cod = nullptr;

    std::shared_ptr<AccountModel> model;
    std::shared_ptr<AccountView> view;
    AccountItemDelegate * delegate = nullptr;
    AccountProxy * proxy           = nullptr;

    DialogAddEdit * dialog = nullptr;

    QLineEdit * passwordLine     = nullptr;
    QAction * loadAction         = nullptr;
    QAction * saveAction         = nullptr;
    QAction * saveAsAction       = nullptr;
    QAction * languageAction     = nullptr;
    QAction * restartAction      = nullptr;
    QAction * restartWarning     = nullptr;
    QAction * restartWarningIcon = nullptr;

    QString curLang;
    QString openedFile;

    QLineEdit * searchLine = nullptr;

    QAction * addAction  = nullptr;
    QAction * editAction = nullptr;
    QAction * delAction  = nullptr;

  private:
    void initAccModel();
    void initConnections();
    QLayout * initMainLayout();
    QToolBar * initTopToolbar();
    QToolBar * initBottomToolbar();
    QWidget * getSpacerWidget();
    QWidget * getMarginWidget(const int margin = 8);
    void successSave(const QString & file);
    bool isSaved;
    void Error(int x);
    void needToClose();

  protected:
    void keyPressEvent(QKeyEvent * ev) override;

  private slots:
    void currentItemValues(const QString & res, const QString & acc, const QString & pas);
    void PassTextChanged(const QString & str);
    void LoadClicked();
    void LanguageClicked();
    void RestartClicked();
    void addClicked();
    void addAccount(const QString & res, const QString & acc, const QString & pas);
    void editClicked();
    void editAccount(const QString & res, const QString & acc, const QString & pas);
    void delClicked();
    void saveClicked();
    void saveAsClicked();
    void clearSelection();
};
