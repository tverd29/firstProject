#include "settingsModel.h"

#include "Source/structs.h"
#include "settings.h"

SettingsModel::SettingsModel(QObject * parent) : QAbstractTableModel(parent) {
}

QVariant SettingsModel::data(const QModelIndex & index, int role) const {
    if (index.isValid()) {
        auto row    = index.row();
        auto column = index.column();

        if (role == Qt::DisplayRole) {
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
                        return Settings::Instance()->getDefaultFileAlias();
                    case SettingsRows::Language:
                        return Settings::Instance()->getLanguageAlias();
                }
            }
        } else if (role == Qt::UserRole) {
            if (column == SettingsColumns::Values) {
                switch (row) {
                    case SettingsRows::Language:
                        return Settings::Instance()->getLanguage();
                }
            }
        }
    }
    return QVariant();
}

bool SettingsModel::setData(const QModelIndex & index, const QVariant & value, int role) {
    if (!index.isValid()) {
        return false;
    }

    auto row    = index.row();
    auto column = index.column();

    if (column == SettingsColumns::Values) {
        switch (row) {
            case SettingsRows::Language:
                Settings::Instance()->setLanguage(value.toString());
                emit criticalSettingChanged();
                break;
        }
    }

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

Qt::ItemFlags SettingsModel::flags(const QModelIndex & index) const {
    if (index.isValid()) {
        auto column = index.column();
        switch (column) {
            case SettingsColumns::Alias:
                return Qt::ItemFlag::ItemIsEnabled;
            case SettingsColumns::Values:
                return Qt::ItemFlag::ItemIsEditable | Qt::ItemFlag::ItemIsEnabled |
                       Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsUserCheckable;
        }
    }
    return QAbstractItemModel::flags(index);
}

int SettingsModel::rowCount(const QModelIndex & parent) const {
    return SettingsRows::RowsCount;
}

int SettingsModel::columnCount(const QModelIndex & parent) const {
    return SettingsColumns::ColumnsCount;
}
