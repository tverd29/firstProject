#pragma once

#include <QListView>
#include <QObject>

class AccountView : public QListView {
    Q_OBJECT

  public:
    explicit AccountView(QWidget * parent = nullptr);
    ~AccountView() = default;

    void mouseReleaseEvent(QMouseEvent * ev) override;
    void mousePressEvent(QMouseEvent * ev) override;
    void mouseDoubleClickEvent(QMouseEvent * ev) override;
    void selectionChanged(const QItemSelection & selected,
                          const QItemSelection & deselected) override;

    void changeSelected(const QModelIndex & index);
    const QModelIndex getCurrentIndex();

  signals:
    void currentAkkSelected(const QString & res, const QString & acc, const QString & pas);
};
