#include "Source/AkksModel/AccountView.h"

#include <QApplication>
#include <QClipboard>
#include <QMouseEvent>
#include <QSortFilterProxyModel>

#include "Source/Popup/Popup.h"
#include "Source/structs.h"

AccountView::AccountView(QWidget * parent) : QTreeView(parent) {
}

void AccountView::mouseReleaseEvent(QMouseEvent * ev) {
    auto index = this->indexAt(ev->pos());
    if (index.isValid()) {
        auto type = index.data(AccountRole::GetType).toInt();
        if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
            return;
        }
        if (this->isDisabledLastIndex) {
            this->changeSelected(index);
        }
        QTreeView::mouseReleaseEvent(ev);
    } else {
        this->clearSelected();
    }
}

void AccountView::mousePressEvent(QMouseEvent * ev) {
    auto index = this->indexAt(ev->pos());
    if (index.isValid()) {
        auto type = index.data(AccountRole::GetType).toInt();
        if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
            auto res = index.data(AccountRole::GetResource).toString();
            if (auto clipBoard = QApplication::clipboard()) {
                clipBoard->setText(res);

                auto popUp = Popup::Instance();
                popUp->setPopupText(tr("copied to the clipboard"));
                popUp->show();
            }
            return;
        }
        QTreeView::mousePressEvent(ev);
    }
}

void AccountView::mouseMoveEvent(QMouseEvent * ev) {
    auto index = this->indexAt(ev->pos());
    if (index.isValid()) {
        auto type = index.data(AccountRole::GetType).toInt();
        if (type == AccountTypes::ACCOUNT_CHILD || type == AccountTypes::PASSWORD_CHILD) {
            return;
        }
        QTreeView::mouseMoveEvent(ev);
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
        emit selectedChanged(false);
    }
    QTreeView::selectionChanged(selected, deselected);
}

void AccountView::keyPressEvent(QKeyEvent * event) {
    auto row = this->currentIndex().row();
    if (event->key() == Qt::Key_Up) {
        if (row > 0) {
            setCurrentIndex(this->model()->index(row - 1, currentIndex().column()));
        }
        return;
    } else if (event->key() == Qt::Key_Down) {
        if (row < this->model()->rowCount() - 1) {
            setCurrentIndex(this->model()->index(row + 1, currentIndex().column()));
        }
        return;
    }
    QTreeView::keyPressEvent(event);
}

void AccountView::changeSelected(const QModelIndex & index) {
    this->model()->setData(index, true, AccountRole::SetSelected);
    this->collapseAll();
    this->expand(index);
    emit selectedChanged(true);
    this->isDisabledLastIndex = false;
}

const QModelIndex AccountView::getCurrentIndex() {
    auto proxy = dynamic_cast<QSortFilterProxyModel *>(this->model());
    return proxy->mapToSource(this->currentIndex());
}

const QString AccountView::getCurrentResource() {
    return this->currentIndex().data(AccountRole::GetResource).toString();
}

const QString AccountView::getCurrentLogin() {
    return this->currentIndex().data(AccountRole::GetAccountName).toString();
}

const QString AccountView::getCurrentPassword() {
    return this->currentIndex().data(AccountRole::GetPassword).toString();
}

void AccountView::clearSelected() {
    this->collapseAll();
    this->model()->setData(QModelIndex(), true, AccountRole::ClearSelection);
    emit clearSelection();
    this->isDisabledLastIndex = true;
}
