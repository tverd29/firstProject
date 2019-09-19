#pragma once

#include <QObject>
#include <QTreeView>

class AccountView : public QTreeView {
    Q_OBJECT

  public:
    explicit AccountView(QWidget * parent = nullptr);
    ~AccountView() = default;

    void mouseReleaseEvent(QMouseEvent * ev) override;
    void mousePressEvent(QMouseEvent * ev) override;
    void mouseMoveEvent(QMouseEvent * ev) override;
    void mouseDoubleClickEvent(QMouseEvent * ev) override;
    void selectionChanged(const QItemSelection & selected,
                          const QItemSelection & deselected) override;
    void keyPressEvent(QKeyEvent * event) override;

    void changeSelected(const QModelIndex & index);
    const QModelIndex getCurrentIndex();

    const QString getCurrentResource();
    const QString getCurrentLogin();
    const QString getCurrentPassword();

    void clearSelected();

  signals:
    void editStart();
    void currentAkkSelected(const QString & res, const QString & acc, const QString & pas);
    void clearSelection();
};
