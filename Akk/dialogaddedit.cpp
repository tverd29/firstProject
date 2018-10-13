#include "dialogaddedit.h"

dialogAddEdit::dialogAddEdit(QDialog *p) {

  parent = p;

  resourceLabel = new QLabel;
  resourceLabel->setText("Resource:");
  loginLabel = new QLabel;
  loginLabel->setText("Account:");
  passwordLabel = new QLabel;
  passwordLabel->setText("Password:");

  resourceLine = new QLineEdit;
  connect(resourceLine, SIGNAL(textChanged(const QString &)), this,
          SLOT(resourceChanged(const QString &)));

  loginLine = new QLineEdit;
  connect(loginLine, SIGNAL(textChanged(const QString &)), this,
          SLOT(loginChanged(const QString &)));

  passwordLine = new QLineEdit;
  connect(passwordLine, SIGNAL(textChanged(const QString &)), this,
          SLOT(passwordChanged(const QString &)));

  ok = new QPushButton();
  ok->setEnabled(false);

  no = new QPushButton("Cancel");
  connect(no, SIGNAL(clicked()), this, SLOT(noClicked()));

  QVBoxLayout *left = new QVBoxLayout;
  left->addWidget(resourceLabel);
  left->addWidget(loginLabel);
  left->addWidget(passwordLabel);

  QVBoxLayout *right = new QVBoxLayout;
  right->addWidget(resourceLine);
  right->addWidget(loginLine);
  right->addWidget(passwordLine);

  QHBoxLayout *top = new QHBoxLayout;
  top->addLayout(left);
  top->addLayout(right);

  QHBoxLayout *bottom = new QHBoxLayout;
  bottom->addWidget(ok);
  bottom->addWidget(no);

  QVBoxLayout *main = new QVBoxLayout;
  main->addLayout(top);
  main->addLayout(bottom);

  setLayout(main);
}

void dialogAddEdit::resourceChanged(QString str) {
  ok->setEnabled(!str.isEmpty() && !loginLine->text().isEmpty() &&
                 !passwordLine->text().isEmpty());
}
void dialogAddEdit::loginChanged(QString str) {
  ok->setEnabled(!resourceLine->text().isEmpty() && !str.isEmpty() &&
                 !passwordLine->text().isEmpty());
}
void dialogAddEdit::passwordChanged(QString str) {
  ok->setEnabled(!resourceLine->text().isEmpty() &&
                 !loginLine->text().isEmpty() && !str.isEmpty());
}
void dialogAddEdit::setLines(QString res, QString akk, QString pass,
                             QString str) {
  resourceLine->setText(res);
  loginLine->setText(akk);
  passwordLine->setText(pass);
  ok->setText(str);
}

Account dialogAddEdit::getAkk() {
  Account akk(resourceLine->text(), loginLine->text(), passwordLine->text());
  return akk;
}
void dialogAddEdit::noClicked() { this->close(); }
