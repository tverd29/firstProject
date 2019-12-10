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
    if (index.isValid() && index.column() == SettingsColumns::Values) {
        switch (index.row()) {
            case SettingsRows::Language:
                auto wgt = dynamic_cast<QComboBox *>(editor);
                wgt->setCurrentIndex(wgt->findData(index.data(Qt::UserRole).toString()));
                return;
        }
    }
    QItemDelegate::setEditorData(editor, index);
}

void SettingsDelegate::setModelData(QWidget * editor, QAbstractItemModel * model,
                                    const QModelIndex & index) const {
    if (index.isValid() && index.column() == SettingsColumns::Values) {
        switch (index.row()) {
            case SettingsRows::Language:
                auto wgt = dynamic_cast<QComboBox *>(editor);
                Settings::Instance()->setLanguage(wgt->currentData().toString());
                return;
        }
    }
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

    switch (index.column()) {
        case SettingsColumns::Alias: {
            QTextOption opt(Qt::AlignVCenter | Qt::AlignLeft);
            painter->drawText(option.rect, index.data().toString(), opt);
            break;
        }
        case SettingsColumns::Values: {
            QTextOption opt(Qt::AlignCenter);
            painter->drawText(option.rect, index.data().toString(), opt);
            break;
        }
    }
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
