#pragma once

#include <QItemDelegate>

class AccountItemDelegate : public QItemDelegate {
    Q_OBJECT

  public:
    explicit AccountItemDelegate(QObject * parent = nullptr);
    ~AccountItemDelegate() = default;

    virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
                       const QModelIndex & index) const override;

    virtual QSize sizeHint(const QStyleOptionViewItem & option,
                           const QModelIndex & index) const override;
};
