#include "Include/AkksModel/AccountProxy.h"

AccountProxy::AccountProxy(QObject * parent) : QSortFilterProxyModel(parent) {
}

void AccountProxy::setFilter(const QString & filter) {
    this->filter = filter;
    invalidateFilter();
}

bool AccountProxy::filterAcceptsRow(int sourceRow, const QModelIndex & sourceParent) const {
    if (filter.isEmpty()) {
        return true;
    }
    QModelIndex index = sourceModel()->index(sourceRow, filterKeyColumn(), sourceParent);
    QString res       = index.data().toString().toLower();
    if (res.contains(filter.toLower())) {
        return true;
    }
    return false;
}

bool AccountProxy::lessThan(const QModelIndex & source_left,
                            const QModelIndex & source_right) const {
    auto leftValue  = source_left.data().toString().toLower();
    auto rightValue = source_right.data().toString().toLower();

    if (leftValue < rightValue) {
        return true;
    }
    return false;
}
