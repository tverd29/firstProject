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

#include "Source/AkksModel/AccountItemDelegate.h"
#include "Source/AkksModel/AccountModel.h"
#include "Source/AkksModel/AccountProxy.h"
#include "Source/AkksModel/AccountView.h"
#include "Source/Popup/Popup.h"
#include "Source/coder.h"
#include "Source/dialogaddedit.h"
#include "Source/structs.h"

AkkWindow::AkkWindow(QWidget * parent) : QMainWindow(parent) {
    this->settings = new QSettings("settings_conf", QSettings::IniFormat);

    this->popUp = Popup::Instance();

    initAccModel();

    cod    = new Coder();
    dialog = new DialogAddEdit(this);

    isSaved = false;

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
    connect(this->dialog, &DialogAddEdit::addAccount, this, &AkkWindow::addAccount);
    connect(this->dialog, &DialogAddEdit::editAccount, this, &AkkWindow::editAccount);

    connect(this->passwordLine, &QLineEdit::textChanged, this, &AkkWindow::PassTextChanged);
    connect(this->loadAction, &QAction::triggered, this, &AkkWindow::LoadClicked);
    connect(this->languageAction, &QAction::triggered, this, &AkkWindow::LanguageClicked);
    connect(this->restartAction, &QAction::triggered, this, &AkkWindow::RestartClicked);

    connect(this->searchLine, &QLineEdit::textChanged, this->proxy, &AccountProxy::setFilter);

    connect(this->addAction, &QAction::triggered, this, &AkkWindow::addClicked);
    connect(this->editAction, &QAction::triggered, this, &AkkWindow::editClicked);
    connect(this->delAction, &QAction::triggered, this, &AkkWindow::delClicked);

    connect(this->saveAction, &QAction::triggered, this, &AkkWindow::saveClicked);
    connect(this->saveAsAction, &QAction::triggered, this, &AkkWindow::saveAsClicked);
}

QLayout * AkkWindow::initMainLayout() {
    searchLine = new QLineEdit;
    searchLine->setPlaceholderText(tr("Search..."));

    QVBoxLayout * main = new QVBoxLayout;
    main->addWidget(searchLine);
    main->addWidget(view.get());

    return main;
}

QToolBar * AkkWindow::initTopToolbar() {
    passwordLine = new QLineEdit();
    passwordLine->setPlaceholderText(tr("Password..."));
    passwordLine->setEchoMode(QLineEdit::Password);
    passwordLine->setFixedWidth(200);

    loadAction = new QAction(QIcon(QPixmap("icons/file_open.png")), tr("load"));
    loadAction->setEnabled(false);

    saveAction = new QAction(QIcon(QPixmap("icons/save.png")), tr("save"));
    saveAction->setEnabled(false);

    saveAsAction = new QAction(QIcon(QPixmap("icons/save_as.png")), tr("save as..."));
    saveAsAction->setEnabled(false);

    QLabel * warning = new QLabel(tr("need to restart app"));
    warning->setVisible(false);
    QLabel * warningIcon = new QLabel();
    warningIcon->setFixedHeight(25);
    warningIcon->setPixmap(QPixmap("icons/warning.png").scaled(25, 25));
    warningIcon->setVisible(false);
    restartAction = new QAction(QIcon(QPixmap("icons/restart.png")), tr("restart"));
    restartAction->setVisible(false);

    settings->beginGroup("main_settings");
    auto x = settings->value("language", "").toString();
    if (settings->value("language", "").toString().contains("ru")) {
        curLang        = "RU";
        languageAction = new QAction(curLang);
    } else if (settings->value("language", "").toString().contains("en")) {
        curLang        = "EN";
        languageAction = new QAction(curLang);
    } else {
        languageAction = new QAction();
    }
    settings->endGroup();

    QToolBar * toolbar = new QToolBar(this);
    toolbar->addWidget(getMarginWidget());
    toolbar->addWidget(passwordLine);
    toolbar->addAction(loadAction);
    toolbar->addSeparator();
    toolbar->addAction(saveAction);
    toolbar->addAction(saveAsAction);
    toolbar->addSeparator();
    restartWarningIcon = toolbar->addWidget(warningIcon);
    restartWarning     = toolbar->addWidget(warning);
    toolbar->addAction(restartAction);
    toolbar->addWidget(getSpacerWidget());
    toolbar->addAction(languageAction);
    toolbar->addWidget(getMarginWidget());
    toolbar->setMovable(false);
    return toolbar;
}

QToolBar * AkkWindow::initBottomToolbar() {
    addAction = new QAction(QIcon(QPixmap("icons/add.png")), tr("Add"));
    addAction->setEnabled(false);

    editAction = new QAction(QIcon(QPixmap("icons/edit.png")), tr("Edit"));
    editAction->setEnabled(false);

    delAction = new QAction(QIcon(QPixmap("icons/del_2.png")), tr("Delete"));
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
        key = passwordLine->text();

        QString tempFile =
            QFileDialog::getOpenFileName(this, tr("Load file"), "", tr("Recommended (*.txt)"));
        if (tempFile.isEmpty()) {
            return;
        }

        openedFile = tempFile;

        QFile file(openedFile);
        QByteArray data;
        QString str;
        if (file.open(QIODevice::ReadOnly)) {
            data = file.readAll();
            str  = QTextCodec::codecForMib(106)->toUnicode(data);
            file.close();
        } else {
            throw 1;
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
            if (akkValues.count() != 3) {
                throw 4;
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
    } catch (int x) {
        Error(x);
    }
}

void AkkWindow::LanguageClicked() {
    settings->beginGroup("main_settings");
    if (languageAction->text() == "RU") {
        languageAction->setText("EN");
        settings->setValue("language", "en_US");
    } else if (languageAction->text() == "EN") {
        languageAction->setText("RU");
        settings->setValue("language", "ru_RU");
    }
    settings->endGroup();

    if (curLang == languageAction->text()) {
        restartWarning->setVisible(false);
        restartWarningIcon->setVisible(false);
        restartAction->setVisible(false);

    } else {
        restartWarning->setVisible(true);
        restartWarningIcon->setVisible(true);
        restartAction->setVisible(true);
    }
}

void AkkWindow::RestartClicked() {
    needToClose();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void AkkWindow::addClicked() {
    dialog->setLines(tr("Add"), true);
    dialog->exec();
}

void AkkWindow::addAccount(const QString & res, const QString & acc, const QString & pas) {
    Account akk;
    akk.resource = res;
    akk.name     = acc;
    akk.password = pas;
    model->insert(akk);
    isSaved = false;
}

void AkkWindow::editClicked() {
    auto curRes = this->view->getCurrentResource();
    auto curLog = this->view->getCurrentLogin();
    auto curPas = this->view->getCurrentPassword();
    dialog->setLines(tr("Edit"), false, curRes, curLog, curPas);
    dialog->exec();
}

void AkkWindow::editAccount(const QString & res, const QString & acc, const QString & pas) {
    model->edit(this->view->getCurrentIndex(), res, acc, pas);
    this->changeEDButEnabled(true);
    isSaved = false;
}

void AkkWindow::delClicked() {
    QMessageBox::StandardButton msg;
    msg = QMessageBox::question(this, tr("Deleting"), tr("Are you sure?"),
                                QMessageBox::Yes | QMessageBox::No);
    if (msg == QMessageBox::Yes) {
        model->remove(this->view->getCurrentIndex());
        isSaved = false;
        this->changeEDButEnabled(model->getRowCount());
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

void AkkWindow::clearSelection() {
    delAction->setEnabled(false);
    editAction->setEnabled(false);
}

void AkkWindow::successSave(const QString & f) {
    try {
        if (f.isEmpty())
            throw 1;
        QFile file(f);
        key = passwordLine->text();
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
            QMessageBox msg;
            msg.setWindowTitle(tr("Saving"));
            msg.setText(tr("Saving complete"));
            msg.exec();

            isSaved = true;
        } else {
            throw 2;
        }
    } catch (int ex) {
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
    updatePopupGeometry();
}

void AkkWindow::moveEvent(QMoveEvent * ev) {
    QMainWindow::moveEvent(ev);
    updatePopupGeometry();
}

void AkkWindow::Error(int x) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error: " + QVariant(x).toString());
    switch (x) {
        case 1:
            msgBox.setText(tr("Error openning file"));
            break;
        case 2:
            msgBox.setText(tr("Save Error"));
            break;
        case 3:
            msgBox.setText(tr("Bad File"));
            break;
        case 4:
            msgBox.setText(tr("Incorrect password"));
    }
    msgBox.exec();
}

void AkkWindow::needToClose() {
    if (!openedFile.isEmpty() && !passwordLine->text().isEmpty()) {
        if (!isSaved) {
            auto msg = QMessageBox::question(this, tr("Saving"), tr("Do you want to save?"),
                                             QMessageBox::Yes | QMessageBox::No);
            if (msg == QMessageBox::Yes) {
                successSave(openedFile);
            }
        }
    }
    isSaved = true;
}

void AkkWindow::changeEDButEnabled(bool value) {
    delAction->setEnabled(value);
    editAction->setEnabled(value);
}

void AkkWindow::updatePopupGeometry() {
    auto topLeft = this->geometry().topLeft();
    topLeft.setX(topLeft.x() + 300);
    topLeft.setY(topLeft.y() + 500);
    this->popUp->updateGeometry(topLeft);
}
