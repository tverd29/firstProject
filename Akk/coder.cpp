#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "openssl.lib")

#include "coder.h"

#include <QTextCodec>

Coder::Coder() {}

QString Coder::Encoding(QString str, QString key) {

  //  QByteArray s = str.toLatin1();
  //  uchar *input = reinterpret_cast<uchar *>(&s);

  //  QStringList s = str.split("");
  //  for (auto &elem : s) {
  //    if (elem != "") {
  //      uchar *input = reinterpret_cast<uchar *>(elem.data());
  //      uchar *output = new uchar();
  //    }
  //  }

  uchar *input = reinterpret_cast<uchar *>(str.data());

  uchar *output = new uchar();

  QByteArray k =
      QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256);
  uchar *userKey = reinterpret_cast<uchar *>(&k);
  AES_KEY aesKey;

  AES_set_encrypt_key(userKey, 256, &aesKey);

  AES_encrypt(input, output, &aesKey);

  QByteArray encrypted = QByteArray(reinterpret_cast<char *>(output));

  str = QTextCodec::codecForMib(106)->toUnicode(encrypted);

  return str;
}

QString Coder::Decoding(QString str, QString key) {

  QByteArray s = str.toUtf8();
  uchar *input = reinterpret_cast<uchar *>(&s);

  uchar *output = new uchar();

  QByteArray k =
      QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256);
  uchar *userKey = reinterpret_cast<uchar *>(&k);
  AES_KEY aesKey;

  AES_set_decrypt_key(userKey, 256, &aesKey);

  AES_decrypt(input, output, &aesKey);

  QByteArray decrypted = QByteArray(reinterpret_cast<char *>(output));
  str = QTextCodec::codecForMib(106)->toUnicode(decrypted);
  return str;
}
