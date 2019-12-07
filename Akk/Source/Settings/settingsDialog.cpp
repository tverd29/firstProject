#include "settingsDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Source/structs.h"
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
    this->settingsView->setModel(this->settingsModel);
    this->settingsView->setItemDelegate(settingsDelegate);

    QHBoxLayout * topLayout = new QHBoxLayout();
    topLayout->setAlignment(Qt::AlignTop);
    topLayout->addWidget(this->settingsView);

    this->acceptButton = new QPushButton(tr("accept"));
    this->cancelButton = new QPushButton(tr("cancel"));

    QHBoxLayout * bottomLayout = new QHBoxLayout();
    bottomLayout->setAlignment(Qt::AlignRight);
    bottomLayout->addWidget(acceptButton);
    bottomLayout->addWidget(cancelButton);

    QVBoxLayout * main = new QVBoxLayout();
    main->addLayout(topLayout);
    main->addLayout(bottomLayout);
    this->setLayout(main);
}
