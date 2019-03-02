#include "Include\akkwindow.h"

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

#include "Include/AkksModel/AccountModel.h"
#include "Include/AkksModel/AccountProxy.h"
#include "Include/AkksModel/AccountView.h"
#include "Include/coder.h"
#include "Include/dialogaddedit.h"
#include "Include/structs.h"

AkkWindow::AkkWindow(QWidget * parent) : QMainWindow(parent) {
    this->settings = new QSettings("settings_conf", QSettings::IniFormat);

    initAccModel();

    cod    = new Coder();
    dialog = new DialogAddEdit(this);

    isSaved = false;

    initToolbar();
    this->addToolBar(Qt::TopToolBarArea, this->toolbar);

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
    this->view->setModel(proxy);
    this->view->setSortingEnabled(true);
    this->view->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    this->view->setRootIsDecorated(false);

    connect(this->view.get(), &AccountView::currentAkkSelected, this,
            &AkkWindow::currentItemValues);
    connect(this->view.get(), &AccountView::doubleClicked, this, &AkkWindow::editClicked);
}

void AkkWindow::initConnections() {
    connect(this->dialog, &DialogAddEdit::addAccount, this, &AkkWindow::addAccount);
    connect(this->dialog, &DialogAddEdit::editAccount, this, &AkkWindow::editAccount);
    connect(this->passwordLine, &QLineEdit::textChanged, this, &AkkWindow::PassTextChanged);
    connect(this->loadAction, &QAction::triggered, this, &AkkWindow::LoadClicked);
    connect(this->languageAction, &QAction::triggered, this, &AkkWindow::LanguageClicked);
    connect(this->restartAction, &QAction::triggered, this, &AkkWindow::RestartClicked);
    connect(this->searchLine, &QLineEdit::textChanged, this->proxy, &AccountProxy::setFilter);
    connect(this->addButton, &QPushButton::clicked, this, &AkkWindow::addClicked);
    connect(this->editButton, &QPushButton::clicked, this, &AkkWindow::editClicked);
    connect(this->delButton, &QPushButton::clicked, this, &AkkWindow::delClicked);
    connect(this->saveAction, &QAction::triggered, this, &AkkWindow::saveClicked);
    connect(this->saveAsAction, &QAction::triggered, this, &AkkWindow::saveAsClicked);
}

QLayout * AkkWindow::initMainLayout() {
    int height = 20;
    int width  = 60;

    QLabel * resLabel = new QLabel;
    resLabel->setMinimumHeight(height);
    resLabel->setMaximumWidth(width);
    resLabel->setText(tr("Resource:"));
    resValLabel = new QLabel;
    resValLabel->setMinimumHeight(height);
    resValLabel->setTextInteractionFlags(resValLabel->textInteractionFlags() |
                                         Qt::TextSelectableByMouse);
    QLabel * logLabel = new QLabel;
    logLabel->setMinimumHeight(height);
    logLabel->setMaximumWidth(width);
    logLabel->setText(tr("Account:"));
    logValLabel = new QLabel;
    logValLabel->setMinimumHeight(height);
    logValLabel->setTextInteractionFlags(logValLabel->textInteractionFlags() |
                                         Qt::TextSelectableByMouse);
    QLabel * pasLabel = new QLabel;
    pasLabel->setMinimumHeight(height);
    pasLabel->setMaximumWidth(width);
    pasLabel->setText(tr("Password:"));
    pasValLabel = new QLabel;
    pasValLabel->setMinimumHeight(height);
    pasValLabel->setTextInteractionFlags(pasValLabel->textInteractionFlags() |
                                         Qt::TextSelectableByMouse);

    searchLine = new QLineEdit;
    searchLine->setPlaceholderText(tr("Search..."));

    addButton = new QPushButton(tr("Add"));
    addButton->setEnabled(false);
    addButton->setToolTip(tr("Add"));

    editButton = new QPushButton(tr("Edit"));
    editButton->setEnabled(false);

    delButton = new QPushButton(tr("Delete"));
    delButton->setEnabled(false);

    QVBoxLayout * rightL = new QVBoxLayout;
    rightL->addWidget(addButton);
    rightL->addWidget(editButton);
    rightL->addWidget(delButton);
    rightL->addSpacing(80);

    QVBoxLayout * leftLabels = new QVBoxLayout;
    leftLabels->addWidget(resLabel);
    leftLabels->addWidget(logLabel);
    leftLabels->addWidget(pasLabel);

    QVBoxLayout * rightLabels = new QVBoxLayout;
    rightLabels->addWidget(resValLabel);
    rightLabels->addWidget(logValLabel);
    rightLabels->addWidget(pasValLabel);

    QHBoxLayout * labelsLayout = new QHBoxLayout;
    labelsLayout->addLayout(leftLabels, 1);
    labelsLayout->addLayout(rightLabels, 5);

    QVBoxLayout * left = new QVBoxLayout;
    left->addWidget(searchLine);
    left->addWidget(view.get());
    left->addLayout(labelsLayout);

    QHBoxLayout * main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(rightL);

    return main;
}

void AkkWindow::initToolbar() {
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

    toolbar = new QToolBar(this);
    toolbar->addWidget(passwordLine);
    toolbar->addAction(loadAction);
    toolbar->addSeparator();
    toolbar->addAction(saveAction);
    toolbar->addAction(saveAsAction);
    toolbar->addSeparator();
    restartWarningIcon = toolbar->addWidget(warningIcon);
    restartWarning     = toolbar->addWidget(warning);
    toolbar->addAction(restartAction);
    QWidget * spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    toolbar->addWidget(spacerWidget);
    toolbar->addAction(languageAction);
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

        addButton->setEnabled(true);
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

void AkkWindow::currentItemValues(const QString & res, const QString & acc, const QString & pas) {
    if (!res.isEmpty() && !acc.isEmpty() && !pas.isEmpty()) {
        resValLabel->setText(res);
        logValLabel->setText(acc);
        pasValLabel->setText(pas);
        delButton->setEnabled(true);
        editButton->setEnabled(true);
    } else {
        resValLabel->setText(QString());
        logValLabel->setText(QString());
        pasValLabel->setText(QString());
        delButton->setEnabled(false);
        editButton->setEnabled(false);
    }
}

void AkkWindow::addClicked() {
    dialog->setWindowTitle(tr("Add"));
    dialog->setLines(tr("Add"));
    dialog->exec();
}

void AkkWindow::addAccount(const QString & res, const QString & acc, const QString & pas) {
    Account akk;
    akk.resource = res;
    akk.name     = acc;
    akk.password = pas;
    model->insert(akk);
    isSaved = false;
    editButton->setEnabled(true);
    delButton->setEnabled(true);
}

void AkkWindow::editClicked() {
    dialog->setWindowTitle(tr("Edit"));
    dialog->setLines(tr("Edit"), resValLabel->text(), logValLabel->text(), pasValLabel->text());
    dialog->exec();
}

void AkkWindow::editAccount(const QString & res, const QString & acc, const QString & pas) {
    model->edit(this->view->getCurrentIndex(), res, acc, pas);
    this->currentItemValues(res, acc, pas);
    isSaved = false;
}

void AkkWindow::delClicked() {
    QMessageBox::StandardButton msg;
    msg = QMessageBox::question(this, tr("Deleting"), tr("Are you sure?"),
                                QMessageBox::Yes | QMessageBox::No);
    if (msg == QMessageBox::Yes) {
        model->remove(this->view->getCurrentIndex());
        isSaved = false;
        if (!model->getRowCount()) {
            editButton->setEnabled(false);
            delButton->setEnabled(false);
        }
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
        this->view->selectionModel()->clear();
        resValLabel->setText(QString());
        logValLabel->setText(QString());
        pasValLabel->setText(QString());
        editButton->setEnabled(false);
        delButton->setEnabled(false);
        return;
    } else if (ev->key() == Qt::Key_Delete && delButton->isEnabled()) {
        this->delClicked();
    } else if (ev->key() == Qt::Key_Insert && addButton->isEnabled()) {
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
            QMessageBox::StandardButton msg;
            msg = QMessageBox::question(this, tr("Saving"), tr("Do you want to save?"),
                                        QMessageBox::Yes | QMessageBox::No);
            if (msg == QMessageBox::Yes) {
                successSave(openedFile);
            }
        }
    }
    isSaved = true;
}
