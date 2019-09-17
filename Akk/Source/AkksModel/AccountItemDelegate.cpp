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

    auto type       = index.data(AccountRole::GetType).toInt();
    auto isSelected = index.data(AccountRole::IsSelected).toBool();

    painter->save();
    if (isSelected || type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
        painter->setBrush(QBrush(QColor(240, 248, 255)));
        painter->setPen(QColor(240, 248, 255));
    } else {
        painter->setBrush(QBrush(index.data(Qt::BackgroundRole).value<QColor>()));
        painter->setPen(index.data(Qt::BackgroundRole).value<QColor>());
    }
    painter->drawRect(rect);

    painter->setPen(QColor("black"));
    QFont font = painter->font();

    QRect accPasRect = QRect(rect.left() + 25, rect.top(), 60, rect.height());
    QRect pixRect    = QRect(accPasRect.right() + 8, rect.top() + 3, 14, 14);
    QRect textRect   = QRect(accPasRect.right() + 30, rect.top(),
                           rect.width() - 25 - 20 - accPasRect.width(), rect.height());
    QRect mainTextRect =
        QRect(rect.left() + 5, rect.top() + 5, rect.width() - 5, rect.height() - 5);

    QPixmap pixmap;
    if (option.state & QStyle::State_MouseOver) {
        pixmap.load("icons/save_buffer_highlighted.png");
    } else {
        pixmap.load("icons/save_buffer.png");
    }

    if (type == AccountTypes::ACCOUNT_CHILD) {
        font.setPointSize(font.pointSize() + 1);
        painter->setFont(font);

        painter->drawText(accPasRect, tr("Account: "));
        painter->drawPixmap(pixRect, pixmap);
        painter->drawText(textRect, index.data(AccountRole::GetResource).toString());
    } else if (type == AccountTypes::PASSWORD_CHILD) {
        font.setPointSize(font.pointSize() + 1);
        painter->setFont(font);

        painter->drawText(accPasRect, tr("Password: "));
        painter->drawPixmap(pixRect, pixmap);
        painter->drawText(textRect, index.data(AccountRole::GetResource).toString());

        painter->setPen(QColor(240, 248, 255));
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());
    } else {
        font.setPointSize(font.pointSize() + 3);
        painter->setFont(font);

        painter->drawText(mainTextRect, index.data(AccountRole::GetResource).toString());

        if (!isSelected) {
            painter->setPen(QColor(240, 248, 255));
            painter->drawLine(rect.bottomLeft(), rect.bottomRight());
        }
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
