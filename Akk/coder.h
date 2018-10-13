#ifndef CODER_H
#define CODER_H

#include <QCryptographicHash>
#include <QString>
#include <openssl/aes.h>
#include <openssl/conf.h>
//#include <openssl/err.h>
//#include <openssl/evp.h>
#include <stdio.h>
#include <string>

class Coder {
public:
  Coder();
  QString Encoding(QString str, QString key);
  QString Decoding(QString str, QString key);

private:
};

#endif // CODER_H
