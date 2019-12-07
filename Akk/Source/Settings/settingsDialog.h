#pragma once

#include <QDialog>
#include <QTableView>

class SettingsModel;

class SettingsDialog : public QDialog {
    Q_OBJECT

  private:
    QTableView * settingsView     = nullptr;
    SettingsModel * settingsModel = nullptr;

  public:
    SettingsDialog(QWidget * parrent = nullptr);
    ~SettingsDialog() = default;
};
