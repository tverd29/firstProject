#pragma once

#include <stdio.h>
#include <string>

#include <QCryptographicHash>
#include <QString>

//#include <openssl/aes.h>
//#include <openssl/conf.h>
//#include <openssl/crypto.h>
//#include <openssl/err.h>
//#include <openssl/evp.h>

class Coder {
  public:
    Coder();
    QString Encoding(QString str, QString k);
    QString Decoding(QString str, QString k);

  private:
};
