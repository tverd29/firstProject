#include "settingsDialog.h"

#include <QVBoxLayout>

#include "settings.h"
#include "settingsDelegate.h"
#include "settingsModel.h"

SettingsDialog::SettingsDialog(QWidget * parrent) : QDialog(parrent) {
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint |
                         Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle(tr("Settings"));

    this->settingsModel                 = new SettingsModel(this);
    SettingsDelegate * settingsDelegate = new SettingsDelegate(this);
    this->settingsView                  = new QTableView(this);
    this->settingsView->setItemDelegate(settingsDelegate);

    QVBoxLayout * main = new QVBoxLayout(this);
    main->addWidget(this->settingsView);
    this->setLayout(main);
}
