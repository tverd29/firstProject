#include "Include\dialogaddedit.h"

DialogAddEdit::DialogAddEdit(QDialog * p) : QDialog(p) {
    resourceLabel = new QLabel;
    resourceLabel->setText("Resource:");
    loginLabel = new QLabel;
    loginLabel->setText("Account:");
    passwordLabel = new QLabel;
    passwordLabel->setText("Password:");

    resourceLine = new QLineEdit;
    connect(this->resourceLine, &QLineEdit::textChanged, this, &DialogAddEdit::resourceChanged);

    loginLine = new QLineEdit;
    connect(this->loginLine, &QLineEdit::textChanged, this, &DialogAddEdit::loginChanged);

    passwordLine = new QLineEdit;
    connect(this->passwordLine, &QLineEdit::textChanged, this, &DialogAddEdit::passwordChanged);
    ok = new QPushButton();
    ok->setEnabled(false);

    no = new QPushButton("Cancel");
    connect(this->no, &QPushButton::clicked, this, &DialogAddEdit::noClicked);

    QVBoxLayout * left = new QVBoxLayout;
    left->addWidget(resourceLabel);
    left->addWidget(loginLabel);
    left->addWidget(passwordLabel);

    QVBoxLayout * right = new QVBoxLayout;
    right->addWidget(resourceLine);
    right->addWidget(loginLine);
    right->addWidget(passwordLine);

    QHBoxLayout * top = new QHBoxLayout;
    top->addLayout(left);
    top->addLayout(right);

    QHBoxLayout * bottom = new QHBoxLayout;
    bottom->addWidget(ok);
    bottom->addWidget(no);

    QVBoxLayout * main = new QVBoxLayout;
    main->addLayout(top);
    main->addLayout(bottom);

    setLayout(main);
}

void DialogAddEdit::resourceChanged(QString str) {
    ok->setEnabled(!str.isEmpty() && !loginLine->text().isEmpty() &&
                   !passwordLine->text().isEmpty());
}
void DialogAddEdit::loginChanged(QString str) {
    ok->setEnabled(!resourceLine->text().isEmpty() && !str.isEmpty() &&
                   !passwordLine->text().isEmpty());
}
void DialogAddEdit::passwordChanged(QString str) {
    ok->setEnabled(!resourceLine->text().isEmpty() && !loginLine->text().isEmpty() &&
                   !str.isEmpty());
}
void DialogAddEdit::setLines(QString res, QString akk, QString pass, QString str) {
    resourceLine->setText(res);
    loginLine->setText(akk);
    passwordLine->setText(pass);
    ok->setText(str);
}

void DialogAddEdit::setFocusOnResource() {
    this->resourceLine->setFocus();
}

Account DialogAddEdit::getAkk(bool editPushed) {
    Account akk(resourceLine->text(), loginLine->text(), passwordLine->text());
    if (!editPushed)
        resourceLine->setFocus();
    return akk;
}
void DialogAddEdit::noClicked() {
    this->close();
}
