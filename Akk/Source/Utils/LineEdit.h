#pragma once

#include <QLineEdit>

class LineEdit : public QLineEdit {
    Q_OBJECT

    void mousePressEvent(QMouseEvent * event) override;

  signals:
    void clicked();
};
