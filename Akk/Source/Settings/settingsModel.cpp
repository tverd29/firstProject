#include "settingsModel.h"

#include "Source/structs.h"
#include "settings.h"

SettingsModel::SettingsModel(QObject * parent) : QAbstractTableModel(parent) {
}

QVariant SettingsModel::data(const QModelIndex & index, int role) const {
}

bool SettingsModel::setData(const QModelIndex & index, const QVariant & value, int role) {
}

QVariant SettingsModel::headerData(int section, Qt::Orientation orientation, int role) const {
}

int SettingsModel::rowCount(const QModelIndex & parent) const {
    return SettingsRows::RowsCount;
}

int SettingsModel::columnCount(const QModelIndex & parent) const {
    return SettingsColumns::ColumnsCount;
}
