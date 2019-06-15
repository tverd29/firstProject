#include "Source/AkksModel/AccountItemDelegate.h"

#include <QPainter>

AccountItemDelegate::AccountItemDelegate(QObject * parent) : QItemDelegate(parent) {
}

void AccountItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option,
                                const QModelIndex & index) const {
    QItemDelegate::paint(painter, option, index);
}

QSize AccountItemDelegate::sizeHint(const QStyleOptionViewItem & option,
                                    const QModelIndex & index) const {
    if (!index.isValid()) {
        return QSize();
    }
    QSize size = QItemDelegate::sizeHint(option, index);
    if (option.state & QStyle::State_Selected) {
        size.setHeight(50);
    } else {
        size.setHeight(20);
    }

    return size;
}
