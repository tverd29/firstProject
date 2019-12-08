#pragma once

#include <QItemDelegate>

class SettingsDelegate : public QItemDelegate {
    Q_OBJECT

  public:
    SettingsDelegate(QObject * parent = nullptr);
    ~SettingsDelegate() override = default;

    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option,
                           const QModelIndex & index) const override;

    void setEditorData(QWidget * editor, const QModelIndex & index) const override;
    void setModelData(QWidget * editor, QAbstractItemModel * model,
                      const QModelIndex & index) const override;

    void paint(QPainter * painter, const QStyleOptionViewItem & option,
               const QModelIndex & index) const override;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override;
};
