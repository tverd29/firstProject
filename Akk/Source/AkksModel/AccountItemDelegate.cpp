#include "Source/AkksModel/AccountItemDelegate.h"

#include <QPainter>

#include "Source/structs.h"

AccountItemDelegate::AccountItemDelegate(QObject * parent) : QItemDelegate(parent) {
}

void AccountItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option,
                                const QModelIndex & index) const {
    if (!index.isValid()) {
        return;
    }

    QRect rect = option.rect;

    painter->save();
    if (option.state & QStyle::State_Selected) {
        painter->setBrush(QBrush(QColor(228, 241, 254)));
        painter->setPen(QColor(228, 241, 254));
    } else {
        painter->setBrush(QBrush(index.data(Qt::BackgroundRole).value<QColor>()));
        painter->setPen(index.data(Qt::BackgroundRole).value<QColor>());
    }
    painter->drawRect(rect);

    painter->setPen(QColor("black"));
    painter->drawText(rect.left(), rect.center().y(),
                      index.data(AccountRole::GetResource).toString());
    painter->restore();
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
