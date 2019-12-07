#include "settingsDialog.h"

#include "settings.h"

SettingsDialog::SettingsDialog(QWidget * parrent) : QDialog(parrent) {
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint |
                         Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle(tr("Settings"));
}
