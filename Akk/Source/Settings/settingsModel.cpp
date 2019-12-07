#include "settingsModel.h"

SettingsModel::SettingsModel(QObject * parent) : QAbstractItemModel(parent) {
}

QVariant SettingsModel::data(const QModelIndex & index, int role) const {
}

bool SettingsModel::setData(const QModelIndex & index, const QVariant & value, int role) {
}

QVariant SettingsModel::headerData(int section, Qt::Orientation orientation, int role) const {
}

QModelIndex SettingsModel::index(int row, int column, const QModelIndex & parent) const {
}

QModelIndex SettingsModel::parent(const QModelIndex & index) const {
}

int SettingsModel::rowCount(const QModelIndex & parent) const {
}

int SettingsModel::columnCount(const QModelIndex & parent) const {
}
