#include "akkwindow.h"
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegExp>
#include <QTextCodec>
#include <QTextStream>

void Error(int x);

AkkWindow::AkkWindow(QWidget * parent) : QDialog(parent) {
    cod = new Coder();

    dialog = new dialogAddEdit(this);
    connect(dialog->ok, SIGNAL(clicked()), this, SLOT(addToAkks()));

    isSaved    = false;
    addPushed  = false;
    editPushed = false;

    passwordLine = new QLineEdit;
    passwordLine->setPlaceholderText("Password...");
    passwordLine->setEchoMode(QLineEdit::Password);
    connect(passwordLine, SIGNAL(textChanged(const QString &)), this,
            SLOT(PassTextChanged(const QString &)));

    loadButton = new QPushButton("load");
    loadButton->setEnabled(false);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(LoadClicked()));

    int height = 20;
    int width  = 60;
    resLabel   = new QLabel;
    resLabel->setMinimumHeight(height);
    resLabel->setMaximumWidth(width);
    resLabel->setText("Resource:");
    resValLabel = new QLabel;
    resValLabel->setMinimumHeight(height);
    resValLabel->setTextInteractionFlags(resValLabel->textInteractionFlags() |
                                         Qt::TextSelectableByMouse);
    logLabel = new QLabel;
    logLabel->setMinimumHeight(height);
    logLabel->setMaximumWidth(width);
    logLabel->setText("Account:");
    logValLabel = new QLabel;
    logValLabel->setMinimumHeight(height);
    logValLabel->setTextInteractionFlags(logValLabel->textInteractionFlags() |
                                         Qt::TextSelectableByMouse);
    pasLabel = new QLabel;
    pasLabel->setMinimumHeight(height);
    pasLabel->setMaximumWidth(width);
    pasLabel->setText("Password:");
    pasValLabel = new QLabel;
    pasValLabel->setMinimumHeight(height);
    pasValLabel->setTextInteractionFlags(pasValLabel->textInteractionFlags() |
                                         Qt::TextSelectableByMouse);

    searchLine = new QLineEdit;
    searchLine->setPlaceholderText("Search...");
    connect(searchLine, SIGNAL(textChanged(const QString &)), this,
            SLOT(SearchTextChanged(const QString &)));

    result = new QListWidget;
    connect(result, SIGNAL(currentRowChanged(int)), this, SLOT(currentRow(int)));

    addButton = new QPushButton("Add");
    addButton->setEnabled(false);
    connect(addButton, SIGNAL(clicked()), this, SLOT(addClicked()));

    editButton = new QPushButton("Edit");
    connect(editButton, SIGNAL(clicked()), this, SLOT(editClicked()));
    editButton->setEnabled(false);

    delButton = new QPushButton("Delete");
    connect(delButton, SIGNAL(clicked()), this, SLOT(delClicked()));
    delButton->setEnabled(false);

    saveButton = new QPushButton("save");
    saveButton->setEnabled(false);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveClicked()));

    saveAsButton = new QPushButton("save as...");
    saveAsButton->setEnabled(false);
    connect(saveAsButton, SIGNAL(clicked()), this, SLOT(saveAsClicked()));

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
    left->addWidget(result);
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

    //*************try AES*************
    //  encryptLine = new QLineEdit;
    //  decryptLine = new QLineEdit;
    //  encryptButton = new QPushButton("Encrypt");
    //  connect(encryptButton, SIGNAL(clicked()), this, SLOT(encryptClicked()));
    //  decryptButton = new QPushButton("Decrypt");
    //  connect(decryptButton, SIGNAL(clicked()), this, SLOT(decryptClicked()));

    //  QHBoxLayout *encryptLayout = new QHBoxLayout;
    //  encryptLayout->addWidget(encryptLine);
    //  encryptLayout->addWidget(encryptButton);
    //  QHBoxLayout *decryptLayout = new QHBoxLayout;
    //  decryptLayout->addWidget(decryptLine);
    //  decryptLayout->addWidget(decryptButton);
    //  QVBoxLayout *crypto = new QVBoxLayout;
    //  crypto->addLayout(encryptLayout);
    //  crypto->addLayout(decryptLayout);
    //  main->addLayout(crypto);
    //  passwordLine->setText("12345");
    //*********************************

    setLayout(main);
    setWindowTitle("Akk");
    setMinimumHeight(600);
    setMinimumWidth(600);
}

//*************try AES*************
// void AkkWindow::encryptClicked() {
//  key = passwordLine->text();
//  encryptLine->setText(cod->Encoding(encryptLine->text(), key));
//}
// void AkkWindow::decryptClicked() {
//  key = passwordLine->text();
//  decryptLine->setText(cod->Decoding(decryptLine->text(), key));
//}
//*********************************

AkkWindow::~AkkWindow() {
    if (!openedFile.isEmpty() && !passwordLine->text().isEmpty()) {
        if (!isSaved) {
            QMessageBox::StandardButton msg;
            msg = QMessageBox::question(this, "Saving", "Do you want to save?",
                                        QMessageBox::Yes | QMessageBox::No);
            if (msg == QMessageBox::Yes) {
                successSave(openedFile);
            }
        }
    }
}

void AkkWindow::PassTextChanged(QString str) {
    loadButton->setEnabled(!str.isEmpty());
    if (!openedFile.isEmpty()) {
        saveButton->setEnabled(!str.isEmpty());
        saveAsButton->setEnabled(!str.isEmpty());
    }
}

void AkkWindow::SearchTextChanged(QString str) {
    if (!str.isEmpty()) {
        if (akks.count() > 0) {
            for (int i = 0; i < akks.count(); i++) {
                if (akks[i].getResource().toLower().contains(str.toLower())) {
                    result->item(i)->setHidden(false);
                } else {
                    result->item(i)->setHidden(true);
                }
            }
        }
    } else {
        refreshResult();
        editButton->setEnabled(false);
        delButton->setEnabled(false);
    }
}

void AkkWindow::LoadClicked() {
    try {
        bool er = true;

        key = passwordLine->text();

        akks.clear();
        refreshResult();
        openedFile = QFileDialog::getOpenFileName();
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

        er           = false;
        QString pass = passwordLine->text();

        // Decoding
        if (!str.isEmpty())
            str = cod->Decoding(str, key);

        str.replace(QRegExp("[\n\r]"), "");
        QStringList strList = str.split("<elem>");
        for (auto & elem : strList) {
            if (elem == "") {
                strList.removeOne(elem);
                continue;
            }

            QStringList akkValues = elem.split("|");
            if (akkValues.count() != 3) {
                throw 4;
            }
            Account akk(akkValues[0], akkValues[1], akkValues[2]);

            akks.append(akk);
        }
        refreshResult();
        addButton->setEnabled(true);
        saveButton->setEnabled(true);
        saveAsButton->setEnabled(true);

        searchLine->setFocus();

        isSaved = true;
    } catch (int x) {
        Error(x);
    }
}

void AkkWindow::currentRow(int curRow) {
    if (curRow >= 0) {
        resValLabel->setText(akks[curRow].getResource());
        logValLabel->setText(akks[curRow].getName());
        pasValLabel->setText(akks[curRow].getPassword());
        delButton->setEnabled(true);
        editButton->setEnabled(true);
    }
}

void AkkWindow::addClicked() {
    addPushed = true;
    dialog->setWindowTitle("Add");
    dialog->setLines("", "", "", "Add");
    dialog->exec();

    refreshResult();
    result->setCurrentRow(result->count() - 1);
}

void AkkWindow::editClicked() {
    editPushed  = true;
    int curItem = result->currentRow();
    dialog->setLines(akks[curItem].getResource(), akks[curItem].getName(),
                     akks[curItem].getPassword(), "Edit");
    dialog->setWindowTitle("Edit");
    dialog->exec();

    refreshResult();
    result->setCurrentRow(curItem);
    searchLine->clear();
}

void AkkWindow::delClicked() {
    QMessageBox::StandardButton msg;
    msg = QMessageBox::question(this, "Deleting", "Are you sure?",
                                QMessageBox::Yes | QMessageBox::No);
    if (msg == QMessageBox::Yes) {
        akks.removeAt(result->currentRow());
        refreshResult();
        searchLine->clear();
        if (akks.count() > 0) {
            result->setCurrentRow(result->count() - 1);
        } else {
            delButton->setEnabled(false);
            editButton->setEnabled(false);
        }

        isSaved = false;
    }
}

void AkkWindow::saveClicked() {
    successSave(openedFile);
}

void AkkWindow::saveAsClicked() {
    QString f = QFileDialog::getSaveFileName();
    if (!f.isEmpty()) {
        successSave(f);
    }
}

void AkkWindow::refreshResult() {
    result->clear();
    for (auto & elem : akks) {
        result->addItem(elem.getResource());
    }
}

void AkkWindow::successSave(QString f) {
    QFile file(f);
    key = passwordLine->text();
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString str = "";
        for (auto & elem : akks) {
            str += elem.getResource() + "|" + elem.getName() + "|" + elem.getPassword() + "<elem>";
        }
        QTextStream writeStream(&file);

        // Encoding
        if (!str.isEmpty())
            str = cod->Encoding(str, key);

        writeStream << str;
        file.close();
        QMessageBox msg;
        msg.setWindowTitle("Saving");
        msg.setText("Saving complete");
        msg.exec();

        isSaved = true;
    } else {
        throw 2;
    }
}

void Error(int x) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error: " + QVariant(x).toString());
    switch (x) {
        case 1:
            msgBox.setText("Error openning file");
            break;
        case 2:
            msgBox.setText("Save Error");
            break;
        case 3:
            msgBox.setText("Bad File");
            break;
        case 4:
            msgBox.setText("Incorrect password");
    }
    msgBox.exec();
}

void AkkWindow::addToAkks() {
    Account akk = dialog->getAkk(editPushed);
    if (addPushed) {
        akks.append(akk);
    }
    if (editPushed) {
        akks[result->currentRow()].setValues(akk.getResource(), akk.getName(), akk.getPassword());
    }
    dialog->close();
    addPushed  = false;
    editPushed = false;
    isSaved    = false;
}
