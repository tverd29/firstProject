#include "settingsDialog.h"

#include <QAction>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
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
    this->settingsView->setMouseTracking(true);

    connect(this->settingsModel, &SettingsModel::criticalSettingChanged, this,
            [&]() { setRestartLayoutVisibility(true); });

    this->settingsView->verticalHeader()->setSectionsClickable(false);
    this->settingsView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->settingsView->verticalHeader()->setVisible(false);

    this->settingsView->setHorizontalHeader(new QHeaderView(Qt::Horizontal, this));
    this->settingsView->horizontalHeader()->setSectionsClickable(false);
    this->settingsView->horizontalHeader()->setSectionResizeMode(SettingsColumns::Alias,
                                                                 QHeaderView::Fixed);
    this->settingsView->horizontalHeader()->setSectionResizeMode(SettingsColumns::Values,
                                                                 QHeaderView::Stretch);

    this->settingsView->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    this->settingsView->resizeRowsToContents();
    this->settingsView->resizeColumnsToContents();

    this->restartWarning = new QLabel(tr("need to restart app"), this);
    QLabel * warningIcon = new QLabel(this);
    warningIcon->setFixedHeight(25);
    warningIcon->setPixmap(QPixmap("icons/warning.png").scaled(25, 25));
    this->restartWarningIcon = warningIcon;
    //    restartAction          = new QAction(QIcon(QPixmap("icons/restart.png")), tr("restart"),
    //    this);
    QWidget * spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->restartButton = new QPushButton(tr("restart"), this);
    connect(this->restartButton, &QPushButton::clicked, this, [&]() {
        emit restartApp();
        this->accept();
    });

    this->restartLayout = new QHBoxLayout();
    this->restartLayout->setAlignment(Qt::AlignLeft);
    this->restartLayout->addWidget(this->restartWarningIcon);
    this->restartLayout->addWidget(this->restartWarning);
    this->restartLayout->addWidget(spacerWidget);
    this->restartLayout->addWidget(this->restartButton);

    this->acceptButton = new QPushButton(tr("accept"), this);
    connect(this->acceptButton, &QPushButton::clicked, this, &SettingsDialog::accept);
    this->cancelButton = new QPushButton(tr("cancel"), this);
    connect(this->cancelButton, &QPushButton::clicked, this, [&]() {
        this->setRestartLayoutVisibility(false);
        this->reject();
    });

    QHBoxLayout * bottomLayout = new QHBoxLayout();
    bottomLayout->setAlignment(Qt::AlignRight);
    bottomLayout->addWidget(acceptButton);
    bottomLayout->addWidget(cancelButton);
    bottomLayout->setMargin(5);

    this->initViewHeight();

    QVBoxLayout * main = new QVBoxLayout();
    main->setMargin(0);
    main->addWidget(this->settingsView);
    main->addLayout(restartLayout);
    main->addLayout(bottomLayout);
    this->setLayout(main);
    this->setRestartLayoutVisibility(false);
}

void SettingsDialog::initViewHeight() {
    auto viewHeight = this->settingsView->horizontalHeader()->height();
    for (int row = 0; row < SettingsRows::RowsCount; ++row) {
        viewHeight += this->settingsView->rowHeight(row);
    }
    this->settingsView->setFixedHeight(viewHeight);
}

void SettingsDialog::setRestartLayoutVisibility(bool visibility) {
    if (visibility) {
        this->restartLayout->setMargin(5);
    } else {
        this->restartLayout->setMargin(0);
    }

    this->restartWarning->setVisible(visibility);
    this->restartWarningIcon->setVisible(visibility);
    //    this->restartAction->setVisible(visibility);
    this->restartButton->setVisible(visibility);
}
