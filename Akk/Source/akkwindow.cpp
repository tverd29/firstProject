#include "Include\akkwindow.h"

#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QRegExp>
#include <QTextCodec>
#include <QTextStream>

#include "Include/AkksModel/AccountModel.h"
#include "Include/AkksModel/AccountProxy.h"
#include "Include/AkksModel/AccountView.h"
#include "Include/structs.h"

AkkWindow::AkkWindow(QWidget * parent) : QDialog(parent) {
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    cod = new Coder();

    model = std::make_shared<AccountModel>(this);
    view  = std::make_shared<AccountView>(this);
    proxy = new AccountProxy(this);
    proxy->setSourceModel(model.get());
    proxy->setDynamicSortFilter(true);
    view->setModel(proxy);
    view->setSortingEnabled(true);
    view->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    view->setRootIsDecorated(false);

    connect(this->view.get(), &AccountView::currentAkkSelected, this,
            &AkkWindow::currentItemValues);
    connect(this->view.get(), &AccountView::doubleClicked, this, &AkkWindow::editClicked);

    dialog = new DialogAddEdit(this);
    connect(this->dialog, &DialogAddEdit::addAccount, this, &AkkWindow::addAccount);
    connect(this->dialog, &DialogAddEdit::editAccount, this, &AkkWindow::editAccount);

    isSaved = false;

    passwordLine = new QLineEdit;
    passwordLine->setPlaceholderText(tr("Password..."));
    passwordLine->setEchoMode(QLineEdit::Password);
    connect(this->passwordLine, &QLineEdit::textChanged, this, &AkkWindow::PassTextChanged);

    loadButton = new QPushButton(tr("load"));
    loadButton->setEnabled(false);
    connect(this->loadButton, &QPushButton::clicked, this, &AkkWindow::LoadClicked);

    int height        = 20;
    int width         = 60;
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
    connect(this->searchLine, &QLineEdit::textChanged, this->proxy, &AccountProxy::setFilter);

    addButton = new QPushButton(tr("Add"));
    addButton->setEnabled(false);
    connect(this->addButton, &QPushButton::clicked, this, &AkkWindow::addClicked);

    editButton = new QPushButton(tr("Edit"));
    connect(this->editButton, &QPushButton::clicked, this, &AkkWindow::editClicked);
    editButton->setEnabled(false);

    delButton = new QPushButton(tr("Delete"));
    connect(this->delButton, &QPushButton::clicked, this, &AkkWindow::delClicked);
    delButton->setEnabled(false);

    saveButton = new QPushButton(tr("save"));
    saveButton->setEnabled(false);
    connect(this->saveButton, &QPushButton::clicked, this, &AkkWindow::saveClicked);

    saveAsButton = new QPushButton(tr("save as..."));
    saveAsButton->setEnabled(false);
    connect(this->saveAsButton, &QPushButton::clicked, this, &AkkWindow::saveAsClicked);

    QHBoxLayout * passLayout = new QHBoxLayout;
    passLayout->addWidget(passwordLine);
    passLayout->addWidget(loadButton);

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

    QHBoxLayout * midL = new QHBoxLayout;
    midL->addLayout(left);
    midL->addLayout(rightL);

    QHBoxLayout * bottom = new QHBoxLayout;
    bottom->addWidget(saveButton, 2);
    bottom->addWidget(saveAsButton, 1);

    QVBoxLayout * main = new QVBoxLayout;
    main->addLayout(passLayout);
    main->addLayout(midL);
    main->addLayout(bottom);

    setLayout(main);
    setWindowTitle("Akk");
    setMinimumHeight(600);
    setMinimumWidth(600);

    passwordLine->setFocus();
}

AkkWindow::~AkkWindow() {
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
}

void AkkWindow::PassTextChanged(const QString & str) {
    loadButton->setEnabled(!str.isEmpty());
    if (!openedFile.isEmpty()) {
        saveButton->setEnabled(!str.isEmpty());
        saveAsButton->setEnabled(!str.isEmpty());
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
        saveButton->setEnabled(true);
        saveAsButton->setEnabled(true);

        searchLine->setFocus();

        isSaved = true;
    } catch (int x) {
        Error(x);
    }
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
    }
    QDialog::keyPressEvent(ev);
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
