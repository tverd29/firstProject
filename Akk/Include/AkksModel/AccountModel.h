#pragma once

#include <QAbstractItemModel>
#include <QVariant>
#include <memory>

#include "Include/AkksModel/AccountItem.h"
#include "Include/structs.h"

class AccountModel : public QAbstractItemModel {
    Q_OBJECT

  private:
    QList<Account *> m_akks;
    AccountItem * rootItem;

  public:
    explicit AccountModel(QObject * parent = nullptr);
    ~AccountModel();

    QVariant data(const QModelIndex & index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex & parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex & index) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;

    void reloadModel(QList<Account> & akks);

  private:
    void clearModel();
};
