#include "Include/AkksModel/AccountView.h"

#include <QMouseEvent>
#include <QSortFilterProxyModel>

#include "Include/structs.h"

AccountView::AccountView(QWidget * parent) : QListView(parent) {
}

void AccountView::mouseReleaseEvent(QMouseEvent * ev) {
}

void AccountView::mousePressEvent(QMouseEvent * ev) {
    auto index = this->indexAt(ev->pos());
    if (index.isValid()) {
        changeSelected(index);
    }
    QListView::mousePressEvent(ev);
}

void AccountView::mouseDoubleClickEvent(QMouseEvent * ev) {
    QListView::mouseDoubleClickEvent(ev);
}

void AccountView::selectionChanged(const QItemSelection & selected,
                                   const QItemSelection & deselected) {
    if (selected.indexes().count()) {
        auto index = selected.indexes().first();
        if (index.isValid()) {
            changeSelected(index);
        }
    } else {
        emit currentAkkSelected(QString(), QString(), QString());
    }
    QListView::selectionChanged(selected, deselected);
}

void AccountView::changeSelected(const QModelIndex & index) {
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
