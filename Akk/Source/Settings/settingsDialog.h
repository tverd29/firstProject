#pragma once

#include <QDialog>
#include <QPushButton>

class SettingsView;
class SettingsModel;

class SettingsDialog : public QDialog {
    Q_OBJECT

  private:
    SettingsView * settingsView   = nullptr;
    SettingsModel * settingsModel = nullptr;

    QPushButton * acceptButton = nullptr;
    QPushButton * cancelButton = nullptr;

  public:
    SettingsDialog(QWidget * parrent = nullptr);
    ~SettingsDialog() = default;
};
