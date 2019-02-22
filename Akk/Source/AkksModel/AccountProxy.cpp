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
