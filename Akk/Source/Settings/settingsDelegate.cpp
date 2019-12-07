#include "settingsDelegate.h"

SettingsDelegate::SettingsDelegate(QObject * parent) : QItemDelegate(parent) {
}

QWidget * SettingsDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option,
                                         const QModelIndex & index) const {
}

void SettingsDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const {
}

void SettingsDelegate::setModelData(QWidget * editor, QAbstractItemModel * model,
                                    const QModelIndex & index) const {
}

QSize SettingsDelegate::sizeHint(const QStyleOptionViewItem & option,
                                 const QModelIndex & index) const {
}
