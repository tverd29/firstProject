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

    auto type = index.data(AccountRole::GetType).toInt();

    painter->save();
    if (option.state & QStyle::State_Selected || type == AccountTypes::ACCOUNT_CHILD ||
        type == AccountTypes::PASSWORD_CHILD) {
        painter->setBrush(QBrush(QColor(228, 241, 254)));
        painter->setPen(QColor(228, 241, 254));
    } else {
        painter->setBrush(QBrush(index.data(Qt::BackgroundRole).value<QColor>()));
        painter->setPen(index.data(Qt::BackgroundRole).value<QColor>());
    }
    painter->drawRect(rect);

    painter->setPen(QColor("black"));
    if (type == AccountTypes::ACCOUNT_CHILD) {
        painter->drawText(rect.left() + 25, rect.center().y() + 2,
                          tr("Account: ") + index.data(AccountRole::GetResource).toString());
    } else if (type == AccountTypes::PASSWORD_CHILD) {
        painter->drawText(rect.left() + 25, rect.center().y() + 2,
                          tr("Password: ") + index.data(AccountRole::GetResource).toString());
    } else {
        painter->drawText(rect.left() + 5, rect.center().y() + 2,
                          index.data(AccountRole::GetResource).toString());
    }

    painter->restore();
}

QSize AccountItemDelegate::sizeHint(const QStyleOptionViewItem & option,
                                    const QModelIndex & index) const {
    if (!index.isValid()) {
        return QSize();
    }

    QSize size = QItemDelegate::sizeHint(option, index);
    auto type  = index.data(AccountRole::GetType).toInt();
    if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
        size.setHeight(20);
    } else {
        size.setHeight(30);
    }

    return size;
}
