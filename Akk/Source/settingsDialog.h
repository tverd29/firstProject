#pragma once

#include <QDialog>

class SettingsDialog : public QDialog {
    Q_OBJECT

  public:
    SettingsDialog(QWidget * parrent = nullptr);
    ~SettingsDialog() = default;
};
