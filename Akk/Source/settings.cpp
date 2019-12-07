#include "settings.h"

Settings * Settings::m_settings = nullptr;

Settings * Settings::Instance() {
    if (!m_settings) {
        m_settings = new Settings();
    }
    return m_settings;
}

const QString Settings::getLanguage() {
    settings->beginGroup("main_settings");
    auto language = settings->value("language", "").toString();
    settings->endGroup();

    return language;
}

void Settings::setLanguage(const QString & language) {
    settings->beginGroup("main_settings");
    settings->setValue("language", language);
    settings->endGroup();
}

Settings::Settings(QObject * parent) : QObject(parent) {
    this->settings = new QSettings("settings_conf", QSettings::IniFormat);
}
