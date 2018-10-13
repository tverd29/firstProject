#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "openssl.lib")

#include "coder.h"

#include <QTextCodec>

Coder::Coder() {}

QString Coder::Encoding(QString str, QString key) {

  //Формирую нужные данные
  QByteArray s = str.toUtf8();
  uchar *input = reinterpret_cast<uchar *>(s.data());
  uchar *output = new uchar();
  QByteArray k =
      QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256)
          .toHex();
  uchar *userKey = reinterpret_cast<uchar *>(k.data());
  AES_KEY *aesKey = new AES_KEY;

  // Шифрование
  AES_set_encrypt_key(userKey, 256, aesKey);
  AES_encrypt(input, output, aesKey);

  //Получение результата
  QByteArray encrypted = QByteArray(reinterpret_cast<char *>(output)).toHex();
  str = QTextCodec::codecForMib(106)->toUnicode(encrypted);
  return str;
}

QString Coder::Decoding(QString str, QString key) {

  QByteArray s = str.toUtf8();
  uchar *input = reinterpret_cast<uchar *>(s.data());
  uchar *output = new uchar();
  QByteArray k =
      QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256)
          .toHex();
  uchar *userKey = reinterpret_cast<uchar *>(k.data());
  AES_KEY aesKey;

  AES_set_decrypt_key(userKey, 256, &aesKey);
  AES_decrypt(input, output, &aesKey);

  QByteArray decrypted = QByteArray(reinterpret_cast<char *>(output)).toHex();
  str = QTextCodec::codecForMib(106)->toUnicode(decrypted);
  return str;
}
