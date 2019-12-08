#include "settingsModel.h"

#include "Source/structs.h"
#include "settings.h"

SettingsModel::SettingsModel(QObject * parent) : QAbstractTableModel(parent) {
}

QVariant SettingsModel::data(const QModelIndex & index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        auto row    = index.row();
        auto column = index.column();

        if (column == SettingsColumns::Alias) {
            switch (row) {
                case SettingsRows::DefaultFile:
                    return tr("Default file");
                case SettingsRows::Language:
                    return tr("Language");
            }
        } else if (column == SettingsColumns::Values) {
            switch (row) {
                case SettingsRows::DefaultFile:
                    return Settings::Instance()->getDefaultFile();
                case SettingsRows::Language:
                    return Settings::Instance()->getLanguage();
            }
        }
    }
    return QVariant();
}

bool SettingsModel::setData(const QModelIndex & index, const QVariant & value, int role) {
    return true;
}

QVariant SettingsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case SettingsColumns::Alias:
                return tr("Setting name");
            case SettingsColumns::Values:
                return tr("Setting value");
        }
    }
    return QVariant();
}

int SettingsModel::rowCount(const QModelIndex & parent) const {
    return SettingsRows::RowsCount;
}

int SettingsModel::columnCount(const QModelIndex & parent) const {
    return SettingsColumns::ColumnsCount;
}
