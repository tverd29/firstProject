#include "Source\akkwindow.h"

#include <QApplication>
#include <QComboBox>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QProcess>
#include <QRegExp>
#include <QTextCodec>
#include <QTextStream>
#include <QToolBar>

#include "AkksModel/AccountItemDelegate.h"
#include "AkksModel/AccountModel.h"
#include "AkksModel/AccountProxy.h"
#include "AkksModel/AccountView.h"
#include "Popup/Popup.h"
#include "Settings/settings.h"
#include "Settings/settingsDialog.h"
#include "Utils/LineEdit.h"
#include "coder.h"
#include "dialogaddedit.h"
#include "structs.h"

AkkWindow::AkkWindow(QWidget * parent) : QMainWindow(parent) {
    this->popUp = Popup::Instance();

    this->defaultFile = Settings::Instance()->getDefaultFile();

    initAccModel();

    this->cod            = new Coder();
    this->accountDialog  = new DialogAddEdit(this);
    this->settingsDialog = new SettingsDialog(this);

    this->addToolBar(Qt::TopToolBarArea, initTopToolbar());
    this->addToolBar(Qt::BottomToolBarArea, initBottomToolbar());

    QWidget * w = new QWidget(this);
    w->setLayout(initMainLayout());
    initConnections();

    setCentralWidget(w);
    setWindowTitle("Akk");
    setFixedHeight(600);
    setFixedWidth(600);

    passwordLine->setFocus();
}

AkkWindow::~AkkWindow() {
    needToClose();
}

void AkkWindow::initAccModel() {
    this->model = std::make_shared<AccountModel>(this);
    this->view  = std::make_shared<AccountView>(this);

    this->proxy = new AccountProxy(this);
    this->proxy->setSourceModel(model.get());
    this->proxy->setDynamicSortFilter(true);

    this->delegate = new AccountItemDelegate(this);

    this->view->setModel(proxy);
    this->view->setItemDelegate(delegate);
    this->view->setSortingEnabled(true);
    this->view->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    this->view->setRootIsDecorated(false);
    this->view->setUniformRowHeights(false);
    this->view->setIndentation(0);

    connect(this->view.get(), &AccountView::selectedChanged, this, &AkkWindow::changeEDButEnabled);
    connect(this->view.get(), &AccountView::editStart, this, &AkkWindow::editClicked);
    connect(this->view.get(), &AccountView::clearSelection, this, &AkkWindow::clearSelection);
    connect(this->model.get(), &AccountModel::addedItem, this->view.get(), &AccountView::addedItem);
}

void AkkWindow::initConnections() {
    connect(this->accountDialog, &DialogAddEdit::addAccount, this, &AkkWindow::addAccount);
    connect(this->accountDialog, &DialogAddEdit::editAccount, this, &AkkWindow::editAccount);
    connect(this->accountDialog, &DialogAddEdit::isResourceValid, this,
            &AkkWindow::isResourceValid);

    connect(this->passwordLine, &QLineEdit::textChanged, this, &AkkWindow::PassTextChanged);
    connect(this->passwordLine, &LineEdit::clicked, this, [&]() { this->passwordLine->clear(); });
    connect(this->loadAction, &QAction::triggered, this, &AkkWindow::LoadClicked);

    connect(this->settingsDialog, &SettingsDialog::restartApp, this, &AkkWindow::setNeedRestart);

    connect(this->searchLine, &QLineEdit::textChanged, this->proxy, &AccountProxy::setFilter);
    connect(this->searchLine, &LineEdit::clicked, this, [&]() { this->searchLine->clear(); });

    connect(this->addAction, &QAction::triggered, this, &AkkWindow::addClicked);
    connect(this->editAction, &QAction::triggered, this, &AkkWindow::editClicked);
    connect(this->delAction, &QAction::triggered, this, &AkkWindow::delClicked);

    connect(this->saveAction, &QAction::triggered, this, &AkkWindow::saveClicked);
    connect(this->saveAsAction, &QAction::triggered, this, &AkkWindow::saveAsClicked);

    connect(this->settingsAction, &QAction::triggered, this, &AkkWindow::settingsClicked);
}

QLayout * AkkWindow::initMainLayout() {
    searchLine = new LineEdit(this);
    searchLine->setPlaceholderText(tr("Search..."));

    QVBoxLayout * main = new QVBoxLayout;
    main->addWidget(searchLine);
    main->addWidget(view.get());

    return main;
}

QToolBar * AkkWindow::initTopToolbar() {
    passwordLine = new LineEdit(this);
    passwordLine->setPlaceholderText(tr("Password..."));
    passwordLine->setEchoMode(QLineEdit::Password);
    passwordLine->setFixedWidth(200);

    if (this->defaultFile.isEmpty()) {
        loadAction = new QAction(QIcon(QPixmap("icons/file_open.png")), tr("load"), this);
        loadAction->setEnabled(false);
    } else {
        loadAction = new QAction(QIcon(QPixmap("icons/accept.png")), tr("load"), this);
        loadAction->setEnabled(false);
    }

    saveAction = new QAction(QIcon(QPixmap("icons/save.png")), tr("save"), this);
    saveAction->setEnabled(false);

    saveAsAction = new QAction(QIcon(QPixmap("icons/save_as.png")), tr("save as..."), this);
    saveAsAction->setEnabled(false);

    settingsAction = new QAction(QIcon(QPixmap("icons/settings.png")), tr("settings"), this);
    settingsAction->setEnabled(true);

    QToolBar * toolbar = new QToolBar(this);
    toolbar->addWidget(getMarginWidget());
    toolbar->addWidget(passwordLine);
    toolbar->addAction(loadAction);
    toolbar->addSeparator();
    toolbar->addAction(saveAction);
    toolbar->addAction(saveAsAction);
    toolbar->addSeparator();
    toolbar->addAction(settingsAction);
    toolbar->addWidget(getSpacerWidget());
    toolbar->setMovable(false);
    return toolbar;
}

QToolBar * AkkWindow::initBottomToolbar() {
    addAction = new QAction(QIcon(QPixmap("icons/add.png")), tr("Add"), this);
    addAction->setEnabled(false);

    editAction = new QAction(QIcon(QPixmap("icons/edit.png")), tr("Edit"), this);
    editAction->setEnabled(false);

    delAction = new QAction(QIcon(QPixmap("icons/del_2.png")), tr("Delete"), this);
    delAction->setEnabled(false);

    QToolBar * toolbar = new QToolBar(this);

    toolbar->addWidget(getSpacerWidget());
    toolbar->addAction(addAction);
    toolbar->addWidget(getSpacerWidget());
    toolbar->addAction(editAction);
    toolbar->addWidget(getSpacerWidget());
    toolbar->addAction(delAction);
    toolbar->addWidget(getSpacerWidget());
    toolbar->setMovable(false);
    return toolbar;
}

QWidget * AkkWindow::getSpacerWidget() {
    QWidget * spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return spacerWidget;
}

QWidget * AkkWindow::getMarginWidget(const int margin) {
    QWidget * marginWidget = new QWidget(this);
    marginWidget->setFixedWidth(margin);
    return marginWidget;
}

void AkkWindow::PassTextChanged(const QString & str) {
    loadAction->setEnabled(!str.isEmpty());
    if (!openedFile.isEmpty()) {
        saveAction->setEnabled(!str.isEmpty());
        saveAsAction->setEnabled(!str.isEmpty());
    }
}

void AkkWindow::LoadClicked() {
    try {
        savingQuestion();

        auto key = passwordLine->text();

        if (this->defaultFile.isEmpty()) {
            QString tempFile =
                QFileDialog::getOpenFileName(this, tr("Load file"), "", tr("Recommended (*.txt)"));
            if (tempFile.isEmpty()) {
                return;
            }
            openedFile = tempFile;
        } else {
            openedFile = this->defaultFile;
        }

        QFile file(openedFile);
        QByteArray data;
        QString str;
        if (file.open(QIODevice::ReadOnly)) {
            data = file.readAll();
            str  = QTextCodec::codecForMib(106)->toUnicode(data);
            file.close();
        } else {
            throw AkkErrors::Error_OpenFile;
        }
        QString pass = passwordLine->text();

        // -----------Decoding------------
        if (!str.isEmpty())
            str = cod->Decoding(str, key);
        // -------------------------------

        str.replace(QRegExp("[\n\r]"), "");
        QStringList strList = str.split("<elem>");
        QList<Account> akks;
        for (auto & elem : strList) {
            if (elem == "") {
                strList.removeOne(elem);
                continue;
            }

            QStringList akkValues = elem.split("|");
            if (akkValues.count() != 3 && !str.contains("<elem>")) {
                throw AkkErrors::Error_IncorrectPassword;
            }

            Account akk;
            akk.resource = akkValues[0];
            akk.name     = akkValues[1];
            akk.password = akkValues[2];
            akks.append(akk);
        }

        model->reloadModel(akks);

        addAction->setEnabled(true);

        saveAction->setEnabled(true);
        saveAsAction->setEnabled(true);

        searchLine->setFocus();

        isSaved = true;

        popUp->setPopupText(tr("Loading %1 complete").arg(getFileName()));
        popUp->show();
    } catch (AkkErrors x) {
        Error(x);
    }
}

void AkkWindow::isResourceValid(const QString & res) {
    accountDialog->resourceValidAnswer(res, this->model->isResourceValid(res));
}

void AkkWindow::addClicked() {
    accountDialog->setLines(tr("Add"), true);
    accountDialog->exec();
}

void AkkWindow::addAccount(const QString & res, const QString & acc, const QString & pas) {
    Account akk;
    akk.resource = res;
    akk.name     = acc;
    akk.password = pas;
    model->insert(akk);
    isSaved = false;

    popUp->setPopupText(tr("%1 added").arg(res));
    popUp->show();
}

void AkkWindow::editClicked() {
    auto curRes = this->view->getCurrentResource();
    auto curLog = this->view->getCurrentLogin();
    auto curPas = this->view->getCurrentPassword();
    accountDialog->setLines(tr("Edit"), false, curRes, curLog, curPas);
    accountDialog->exec();
}

void AkkWindow::editAccount(const QString & res, const QString & acc, const QString & pas) {
    model->edit(this->view->getCurrentIndex(), res, acc, pas);
    this->changeEDButEnabled(true);
    isSaved = false;

    popUp->setPopupText(tr("%1 edited").arg(res));
    popUp->show();
}

void AkkWindow::delClicked() {
    QMessageBox::StandardButton msg;
    msg = QMessageBox::question(this, tr("Deleting"), tr("Are you sure?"),
                                QMessageBox::Yes | QMessageBox::No);
    if (msg == QMessageBox::Yes) {
        auto deletedRes = this->view->getCurrentResource();

        model->remove(this->view->getCurrentIndex());
        isSaved = false;
        this->changeEDButEnabled(model->getRowCount());

        popUp->setPopupText(tr("%1 deleted").arg(deletedRes));
        popUp->show();
    }
}

void AkkWindow::saveClicked() {
    successSave(openedFile);
}

void AkkWindow::saveAsClicked() {
    QString f = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("Recommended (*.txt)"));
    if (!f.isEmpty()) {
        successSave(f);
    }
}

void AkkWindow::settingsClicked() {
    Settings::Instance()->save();
    if (!settingsDialog->exec()) {
        Settings::Instance()->restore();
    } else {
        popUp->setPopupText(tr("Settings accepted"));
        popUp->show();
        if (this->needRestart) {
            this->restartApp();
        }
    }
}

void AkkWindow::clearSelection() {
    delAction->setEnabled(false);
    editAction->setEnabled(false);
}

void AkkWindow::setNeedRestart() {
    this->needRestart = true;
}

void AkkWindow::successSave(const QString & f) {
    try {
        if (f.isEmpty())
            throw AkkErrors::Error_OpenFile;
        QFile file(f);
        auto key = passwordLine->text();
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QString str         = "";
            QList<Account> akks = model->getAllAkks();
            for (auto & elem : akks) {
                str += elem.resource + "|" + elem.name + "|" + elem.password + "<elem>";
            }
            QTextStream writeStream(&file);

            // -----------Encoding-------------
            if (!str.isEmpty())
                str = cod->Encoding(str, key);
            // --------------------------------

            writeStream << str;
            file.close();

            popUp->setPopupText(tr("Saving %1 complete").arg(this->getFileName()));
            popUp->show();

            isSaved = true;
        } else {
            throw AkkErrors::Error_SaveFile;
        }
    } catch (AkkErrors ex) {
        Error(ex);
    }
}

void AkkWindow::keyPressEvent(QKeyEvent * ev) {
    if (ev->key() == Qt::Key_Escape) {
        this->view->clearSelected();
        return;
    } else if (ev->key() == Qt::Key_Delete && delAction->isEnabled()) {
        this->delClicked();
    } else if (ev->key() == Qt::Key_Insert && addAction->isEnabled()) {
        this->addClicked();
    } else if (ev->key() == Qt::Key_Enter) {
        if (passwordLine->hasFocus()) {
            this->LoadClicked();
        } else if (view->hasFocus()) {
            this->editClicked();
        }
    }
    QMainWindow::keyPressEvent(ev);
}

void AkkWindow::paintEvent(QPaintEvent * ev) {
    QMainWindow::paintEvent(ev);
    updatePopupCenter();
}

void AkkWindow::moveEvent(QMoveEvent * ev) {
    QMainWindow::moveEvent(ev);
    updatePopupCenter();
}

void AkkWindow::Error(int x) {
    switch (x) {
        case AkkErrors::Error_OpenFile:
            popUp->setPopupText(tr("Error openning file"));
            break;
        case AkkErrors::Error_SaveFile:
            popUp->setPopupText(tr("Save Error"));
            break;
        case AkkErrors::Error_BadFile:
            popUp->setPopupText(tr("Bad File"));
            break;
        case AkkErrors::Error_IncorrectPassword:
            popUp->setPopupText(tr("Incorrect password"));
    }
    popUp->show();
}

void AkkWindow::needToClose() {
    if (!openedFile.isEmpty() && !passwordLine->text().isEmpty()) {
        savingQuestion();
    }
    isSaved = true;
}

void AkkWindow::savingQuestion() {
    if (!isSaved) {
        auto msg = QMessageBox::question(this, tr("Saving"), tr("Do you want to save?"),
                                         QMessageBox::Yes | QMessageBox::No);
        if (msg == QMessageBox::Yes) {
            successSave(openedFile);
        }
    }
}

void AkkWindow::changeEDButEnabled(bool value) {
    delAction->setEnabled(value);
    editAction->setEnabled(value);
}

void AkkWindow::updatePopupCenter() {
    QPoint popUpCenter;
    popUpCenter.setX(this->geometry().center().x());
    popUpCenter.setY(this->geometry().bottom() - 100);
    this->popUp->updateCenter(popUpCenter);
}

void AkkWindow::restartApp() {
    needToClose();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

const QString AkkWindow::getFileName() const {
    if (this->openedFile.isEmpty()) {
        return QString();
    }
    return this->openedFile.split("/").last();
}
