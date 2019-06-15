#pragma once

#include <QAbstractItemModel>
#include <QVariant>
#include <memory>

#include "Source/structs.h"

class AccountItem;

class AccountModel : public QAbstractItemModel {
    Q_OBJECT

  private:
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
    void insert(Account & akk);
    void remove(const QModelIndex & index);
    void edit(const QModelIndex & index, const QString & res, const QString & acc,
              const QString & pas);
    QList<Account> getAllAkks();
    int getRowCount();

  private:
    void clearModel();
};
