#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <memory>

class AccountItemDelegate;
class AccountModel;
class AccountView;
class AccountProxy;
class Coder;
class DialogAddEdit;
class Popup;
class LineEdit;

enum AkkErrors { Error_OpenFile, Error_SaveFile, Error_BadFile, Error_IncorrectPassword };

class AkkWindow : public QMainWindow {
    Q_OBJECT

  public:
    AkkWindow(QWidget * parent = nullptr);
    ~AkkWindow() override;

  private:
    Popup * popUp = nullptr;

    Coder * cod = nullptr;

    std::shared_ptr<AccountModel> model;
    std::shared_ptr<AccountView> view;
    AccountItemDelegate * delegate = nullptr;
    AccountProxy * proxy           = nullptr;

    DialogAddEdit * accountDialog = nullptr;

    LineEdit * passwordLine      = nullptr;
    QAction * loadAction         = nullptr;
    QAction * saveAction         = nullptr;
    QAction * saveAsAction       = nullptr;
    QAction * settingsAction     = nullptr;
    QAction * languageAction     = nullptr;
    QAction * restartAction      = nullptr;
    QAction * restartWarning     = nullptr;
    QAction * restartWarningIcon = nullptr;

    QString curLang;
    QString openedFile;

    LineEdit * searchLine = nullptr;

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
    bool isSaved = true;
    void Error(int x);
    void needToClose();
    void savingQuestion();

    void updatePopupGeometry();

    const QString getFileName() const;

  protected:
    void keyPressEvent(QKeyEvent * ev) override;
    void paintEvent(QPaintEvent * ev) override;
    void moveEvent(QMoveEvent * ev) override;

  private slots:
    void changeEDButEnabled(bool value);
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
    void settingsClicked();
    void clearSelection();
};
