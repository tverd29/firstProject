#include "settingsDelegate.h"

#include <QComboBox>
#include <QFileDialog>
#include <QPainter>

#include "Source/structs.h"
#include "settings.h"

SettingsDelegate::SettingsDelegate(QObject * parent) : QItemDelegate(parent) {
}

QWidget * SettingsDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option,
                                         const QModelIndex & index) const {
    if (index.isValid() && index.column() == SettingsColumns::Values) {
        switch (index.row()) {
            case SettingsRows::DefaultFile: {
                QString tempFile = QFileDialog::getOpenFileName(parent, tr("Load file"), "",
                                                                tr("Recommended (*.txt)"));
                if (!tempFile.isEmpty()) {
                    Settings::Instance()->setDefaultFile(tempFile);
                }
                return nullptr;
            }
            case SettingsRows::Language: {
                auto wgt   = new QComboBox(parent);
                auto langs = Settings::Instance()->getLanguages();
                for (auto key : langs.keys()) {
                    wgt->addItem(langs.value(key), key);
                }
                return wgt;
            }
        }
    }
    return QItemDelegate::createEditor(parent, option, index);
}

void SettingsDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const {
    QItemDelegate::setEditorData(editor, index);
}

void SettingsDelegate::setModelData(QWidget * editor, QAbstractItemModel * model,
                                    const QModelIndex & index) const {
    QItemDelegate::setModelData(editor, model, index);
}

void SettingsDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option,
                             const QModelIndex & index) const {
    if (index.row() == SettingsRows::DefaultFile) {
        painter->save();

        painter->setPen(QColor("lightgrey"));
        painter->drawLine(option.rect.topLeft(), option.rect.topRight());

        painter->restore();
    }
    QTextOption opt(Qt::AlignVCenter | Qt::AlignLeft);
    painter->drawText(option.rect, index.data().toString(), opt);
}

QSize SettingsDelegate::sizeHint(const QStyleOptionViewItem & option,
                                 const QModelIndex & index) const {
    if (!index.isValid()) {
        return QSize();
    }

    QSize size  = QItemDelegate::sizeHint(option, index);
    auto column = index.column();
    switch (column) {
        case SettingsColumns::Alias:
            size.setWidth(80);
            break;
        case SettingsColumns::Values:
            size.setWidth(220);
            break;
    }
    return size;
}
