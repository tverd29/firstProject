#include "LineEdit.h"

LineEdit::LineEdit(QWidget * parent) : QLineEdit(parent) {
}

void LineEdit::mousePressEvent(QMouseEvent * event) {
    QLineEdit::mousePressEvent(event);
    emit clicked();
}
