#pragma once

#include <QTableView>

class SettingsView : public QTableView {
    Q_OBJECT

  public:
    SettingsView(QWidget * parent = nullptr);
    ~SettingsView() override = default;
};
