#include "coder.h"

#include <QTextCodec>

Coder::Coder() {
}

QString Coder::Encoding(QString str, QString k) {
    QByteArray input = str.toUtf8();
    QByteArray key   = QCryptographicHash::hash(k.toUtf8(), QCryptographicHash::Sha256).toHex();

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
}

QString Coder::Decoding(QString str, QString k) {
    QStringList input = str.split("|");
    QByteArray key    = QCryptographicHash::hash(k.toUtf8(), QCryptographicHash::Sha256).toHex();

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
    for (auto & elem : r) {
        res.append(static_cast<char>(elem));
    }

    return QTextCodec::codecForMib(106)->toUnicode(res);
}
