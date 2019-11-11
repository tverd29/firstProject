#include "LineEdit.h"

void LineEdit::mousePressEvent(QMouseEvent * event) {
    QLineEdit::mousePressEvent(event);
    emit clicked();
}
