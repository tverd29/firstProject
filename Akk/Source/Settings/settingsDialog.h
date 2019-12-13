#pragma once

#include <QDialog>
#include <QPushButton>

class QTableView;
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

  private:
    void initViewHeight();
};
