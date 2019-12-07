#pragma once

#include <QDialog>
#include <QPushButton>
#include <QTableView>

class SettingsModel;

class SettingsDialog : public QDialog {
    Q_OBJECT

  private:
    QTableView * settingsView     = nullptr;
    SettingsModel * settingsModel = nullptr;

    QPushButton * acceptButton = nullptr;
    QPushButton * cancelButton = nullptr;

  public:
    SettingsDialog(QWidget * parrent = nullptr);
    ~SettingsDialog() = default;
};
