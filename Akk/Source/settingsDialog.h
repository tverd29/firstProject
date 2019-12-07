#pragma once

#include <QDialog>

class SettingsDialog : public QDialog {
    Q_OBJECT

    SettingsDialog(QWidget * parrent = nullptr);
    ~SettingsDialog() = default;
};
