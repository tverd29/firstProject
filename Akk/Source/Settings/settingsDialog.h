#pragma once

#include <QDialog>
#include <QPushButton>

class QTableView;
class SettingsModel;
class QHBoxLayout;

class SettingsDialog : public QDialog {
    Q_OBJECT

  private:
    QTableView * settingsView     = nullptr;
    SettingsModel * settingsModel = nullptr;

    QPushButton * restartButton = nullptr;
    //    QAction * restartAction      = nullptr;
    QWidget * restartWarning     = nullptr;
    QWidget * restartWarningIcon = nullptr;

    QPushButton * acceptButton = nullptr;
    QPushButton * cancelButton = nullptr;

    QHBoxLayout * restartLayout = nullptr;

  public:
    SettingsDialog(QWidget * parrent = nullptr);
    ~SettingsDialog() = default;

  private:
    void initViewHeight();
    void setRestartLayoutVisibility(bool visibility = true);

  signals:
    void restartApp();
};
