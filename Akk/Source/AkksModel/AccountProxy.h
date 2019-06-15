#pragma once

#include <QSortFilterProxyModel>

class AccountProxy : public QSortFilterProxyModel {
    Q_OBJECT
  private:
    QString filter;

  public:
    explicit AccountProxy(QObject * parent = nullptr);
    ~AccountProxy() = default;

  protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex & sourceParent) const override;
    virtual bool lessThan(const QModelIndex & source_left,
                          const QModelIndex & source_right) const override;

  public slots:
    void setFilter(const QString & filter);
};
