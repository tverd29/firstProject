#include "Source/AkksModel/AccountView.h"

#include <QMouseEvent>
#include <QSortFilterProxyModel>

#include "Source/structs.h"

AccountView::AccountView(QWidget * parent) : QTreeView(parent) {
}

void AccountView::mouseReleaseEvent(QMouseEvent * ev) {
    QTreeView::mouseReleaseEvent(ev);
}

void AccountView::mousePressEvent(QMouseEvent * ev) {
    auto index = this->indexAt(ev->pos());
    if (index.isValid()) {
        auto type = index.data(AccountRole::GetType).toInt();
        if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
            return;
        }
        QTreeView::mousePressEvent(ev);
    }
}

void AccountView::mouseDoubleClickEvent(QMouseEvent * ev) {
    auto index = this->indexAt(ev->pos());
    if (index.isValid()) {
        auto type = index.data(AccountRole::GetType).toInt();
        if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
            return;
        }
        emit editStart();
    }
}

void AccountView::selectionChanged(const QItemSelection & selected,
                                   const QItemSelection & deselected) {
    if (selected.indexes().count()) {
        auto index = selected.indexes().first();
        if (index.isValid()) {
            auto type = index.data(AccountRole::GetType).toInt();
            if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
                return;
            }
            changeSelected(index);
        }
    } else {
        emit currentAkkSelected(QString(), QString(), QString());
    }
    QTreeView::selectionChanged(selected, deselected);
}

void AccountView::changeSelected(const QModelIndex & index) {
    this->collapseAll();
    this->expand(index);
    QString res = index.data(AccountRole::GetResource).toString();
    QString acc = index.data(AccountRole::GetAccountName).toString();
    QString pas = index.data(AccountRole::GetPassword).toString();
    if (!res.isEmpty() && !acc.isEmpty() && !pas.isEmpty()) {
        emit currentAkkSelected(res, acc, pas);
    }
}

const QModelIndex AccountView::getCurrentIndex() {
    auto proxy = dynamic_cast<QSortFilterProxyModel *>(this->model());
    return proxy->mapToSource(this->currentIndex());
}
