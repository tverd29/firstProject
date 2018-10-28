#include "coder.h"

#include <QTextCodec>

Coder::Coder() {}

QString Coder::Encoding(QString str, QString k) {

  QByteArray input = str.toUtf8();
  QByteArray key =
      QCryptographicHash::hash(k.toUtf8(), QCryptographicHash::Sha256).toHex();

  QList<int> r;

  for (int i = 0; i < input.count();) {
    for (int j = 0; j < key.count(); j++) {
      if (i + j > input.count() - 1)
        break;
      int x = input[i + j];
      int y = key[j];
      r.append(x + y);
    }
    i += key.count();
  }

  QString result;
  for (int i = 0; i < r.count(); i++) {
    result += QString::number(r[i]);
    if (i < r.count() - 1)
      result += "|";
  }

  return result;

  /** TODO сделать openssl
  //Формирую нужные данные
  //  QByteArray s = str.toUtf8();
  //  uchar *input = reinterpret_cast<uchar *>(s.data());
  //  uchar *output = new uchar();
  //  AES_KEY *aesKey = new AES_KEY;
  //  QByteArray k =
  //      QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256)
  //          .toHex();
  //  uchar *userKey = reinterpret_cast<uchar *>(k.data());
  //  uchar *userKey = reinterpret_cast<uchar *>(key.data());
  //  QString iv16 = "507055722b4c4d4876614b6d66307136";
  //  uchar *iv = reinterpret_cast<uchar *>(iv16.data());
  // Шифрование
  //  AES_set_encrypt_key(userKey, 256, aesKey);
  //  AES_encrypt(input, output, aesKey);
  //Получение результата
  //  QByteArray encrypted = QByteArray(reinterpret_cast<char
  //  *>(output)).toHex(); str =
  //  QTextCodec::codecForMib(106)->toUnicode(encrypted);
  //  return str;
  **/
}

QString Coder::Decoding(QString str, QString k) {

  QStringList input = str.split("|");
  QByteArray key =
      QCryptographicHash::hash(k.toUtf8(), QCryptographicHash::Sha256).toHex();

  QList<int> r;

  for (int i = 0; i < input.count();) {
    for (int j = 0; j < key.count(); j++) {
      if (i + j > input.count() - 1)
        break;
      int x = input[i + j].toInt();
      int y = key[j];
      r.append(x - y);
    }
    i += key.count();
  }

  QByteArray res;
  for (auto &elem : r) {
    res.append(static_cast<char>(elem));
  }

  return QTextCodec::codecForMib(106)->toUnicode(res);

  /** TODO сделать openssl
  //Формирую нужные данные
  //  QByteArray s = str.toUtf8();
  //  uchar *input = reinterpret_cast<uchar *>(s.data());
  //  uchar *output = new uchar();
  //  AES_KEY *aesKey = new AES_KEY();
  //  QString iv16 = "507055722b4c4d4876614b6d66307136";
  //  uchar *iv = reinterpret_cast<uchar *>(iv16.data());
  //  QByteArray key =
  //      QCryptographicHash::hash(k.toUtf8(), QCryptographicHash::Sha256)
  //          .toHex();
  //  uchar *userKey = reinterpret_cast<uchar *>(k.data());
  //  uchar *userKey = reinterpret_cast<uchar *>(k.data());
  //  AES_set_decrypt_key(userKey, 256, aesKey);
  //  AES_decrypt(input, output, aesKey);
  //  QByteArray decrypted = QByteArray(reinterpret_cast<char
  //  *>(output)).toHex(); str =
  //  QTextCodec::codecForMib(106)->toUnicode(decrypted);
  //  return str;
  **/
}
