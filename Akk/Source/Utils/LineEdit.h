#pragma once

#include <QLineEdit>

class LineEdit : public QLineEdit {
    Q_OBJECT
  public:
    LineEdit(QWidget * parent = nullptr);

  protected:
    void mousePressEvent(QMouseEvent * event) override;

  signals:
    void clicked();
};
