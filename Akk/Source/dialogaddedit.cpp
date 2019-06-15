#include "Source\dialogaddedit.h"

DialogAddEdit::DialogAddEdit(QWidget * p) : QDialog(p) {
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    resourceLabel = new QLabel;
    resourceLabel->setText(tr("Resource:"));
    loginLabel = new QLabel;
    loginLabel->setText(tr("Account:"));
    passwordLabel = new QLabel;
    passwordLabel->setText(tr("Password:"));

    resourceLine = new QLineEdit;
    connect(this->resourceLine, &QLineEdit::textChanged, this, &DialogAddEdit::resourceChanged);

    loginLine = new QLineEdit;
    connect(this->loginLine, &QLineEdit::textChanged, this, &DialogAddEdit::loginChanged);

    passwordLine = new QLineEdit;
    connect(this->passwordLine, &QLineEdit::textChanged, this, &DialogAddEdit::passwordChanged);
    ok = new QPushButton();
    ok->setEnabled(false);
    connect(this->ok, &QPushButton::clicked, this, &DialogAddEdit::okClicked);

    no = new QPushButton(tr("Cancel"));
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
void DialogAddEdit::setLines(const QString & str, bool isAdding, const QString res,
                             const QString & akk, const QString & pas) {
    this->isAdding = isAdding;

    ok->setText(str);
    resourceLine->setText(res);
    loginLine->setText(akk);
    passwordLine->setText(pas);
    resourceLine->setFocus();
}

void DialogAddEdit::noClicked() {
    this->close();
}

void DialogAddEdit::okClicked() {
    QString res = resourceLine->text();
    QString acc = loginLine->text();
    QString pas = passwordLine->text();
    if (!res.isEmpty() && !acc.isEmpty() && !pas.isEmpty()) {
        if (isAdding) {
            emit addAccount(res, acc, pas);
        } else {
            emit editAccount(res, acc, pas);
        }
    }
    isAdding = false;
    this->close();
}
