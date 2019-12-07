#include "AccountProxy.h"

#include "Source/structs.h"

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
    auto res          = index.data().toString().toLower();
    auto type         = index.data(AccountRole::GetType).toInt();
    if (res.contains(filter.toLower())) {
        return true;
    }
    if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
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
