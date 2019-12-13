#include "settingsDialog.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableView>
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

    this->settingsView->verticalHeader()->setSectionsClickable(false);
    this->settingsView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->settingsView->verticalHeader()->setVisible(false);

    this->settingsView->horizontalHeader()->setSectionsClickable(false);
    this->settingsView->horizontalHeader()->setSectionResizeMode(SettingsColumns::Alias,
                                                                 QHeaderView::Fixed);
    this->settingsView->horizontalHeader()->setSectionResizeMode(SettingsColumns::Values,
                                                                 QHeaderView::Stretch);

    this->acceptButton = new QPushButton(tr("accept"), this);
    connect(this->acceptButton, &QPushButton::clicked, this, &SettingsDialog::accept);

    this->cancelButton = new QPushButton(tr("cancel"), this);
    connect(this->cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);

    QHBoxLayout * bottomLayout = new QHBoxLayout();
    bottomLayout->setAlignment(Qt::AlignRight);
    bottomLayout->addWidget(acceptButton);
    bottomLayout->addWidget(cancelButton);
    bottomLayout->setMargin(5);

    QVBoxLayout * main = new QVBoxLayout();
    main->setMargin(0);
    main->addWidget(this->settingsView);
    main->addLayout(bottomLayout);
    this->setLayout(main);
}
