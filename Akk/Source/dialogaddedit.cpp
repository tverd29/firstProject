#include "dialogaddedit.h"

#include "Popup/Popup.h"

DialogAddEdit::DialogAddEdit(QWidget * p) : QDialog(p) {
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint |
                         Qt::MSWindowsFixedSizeDialogHint);

    resourceLabel = new QLabel(this);
    resourceLabel->setText(tr("Resource:"));
    loginLabel = new QLabel(this);
    loginLabel->setText(tr("Account:"));
    passwordLabel = new QLabel(this);
    passwordLabel->setText(tr("Password:"));

    resourceLine = new QLineEdit(this);
    connect(this->resourceLine, &QLineEdit::textChanged, this, &DialogAddEdit::resourceChanged);

    loginLine = new QLineEdit(this);
    connect(this->loginLine, &QLineEdit::textChanged, this, &DialogAddEdit::loginChanged);

    passwordLine = new QLineEdit(this);
    connect(this->passwordLine, &QLineEdit::textChanged, this, &DialogAddEdit::passwordChanged);
    ok = new QPushButton(this);
    ok->setEnabled(false);
    connect(this->ok, &QPushButton::clicked, this, &DialogAddEdit::okClicked);

    no = new QPushButton(tr("Cancel"), this);
    connect(this->no, &QPushButton::clicked, this, &DialogAddEdit::noClicked);

    QVBoxLayout * left = new QVBoxLayout();
    left->addWidget(resourceLabel);
    left->addWidget(loginLabel);
    left->addWidget(passwordLabel);

    QVBoxLayout * right = new QVBoxLayout();
    right->addWidget(resourceLine);
    right->addWidget(loginLine);
    right->addWidget(passwordLine);

    QHBoxLayout * top = new QHBoxLayout();
    top->addLayout(left);
    top->addLayout(right);

    QHBoxLayout * bottom = new QHBoxLayout();
    bottom->addWidget(ok);
    bottom->addWidget(no);

    QVBoxLayout * main = new QVBoxLayout();
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
    this->oldRes   = QString();
    this->isAdding = isAdding;

    if (!isAdding) {
        this->oldRes = res;
    }

    this->setWindowTitle(str);
    ok->setText(str);
    resourceLine->setText(res);
    loginLine->setText(akk);
    passwordLine->setText(pas);
    resourceLine->setFocus();
}

void DialogAddEdit::resourceValidAnswer(const QString & res, bool isValidRes) {
    if (!isValidRes) {
        auto popUp = Popup::Instance();
        popUp->setPopupText(tr("resource has already been created"));
        popUp->show();
        return;
    }
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
    this->accept();
}

void DialogAddEdit::noClicked() {
    this->reject();
}

void DialogAddEdit::okClicked() {
    QString res = resourceLine->text();
    if (res.toLower() == this->oldRes.toLower()) {
        this->resourceValidAnswer(res);
    } else {
        emit isResourceValid(res);
    }
}
