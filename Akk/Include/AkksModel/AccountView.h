#pragma once

#include <QListView>
#include <QObject>

class AccountView : public QListView {
    Q_OBJECT

  public:
    explicit AccountView(QWidget * parent = nullptr);
    ~AccountView() = default;
};
