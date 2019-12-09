#pragma once

#include <QAbstractTableModel>

class SettingsModel : public QAbstractTableModel {
    Q_OBJECT

  public:
    SettingsModel(QObject * parent = nullptr);
    ~SettingsModel() override = default;

    QVariant data(const QModelIndex & index, int role) const override;
    bool setData(const QModelIndex & index, const QVariant & value,
                 int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
};
