#include "settings.h"

Settings * Settings::m_settings = nullptr;

Settings * Settings::Instance() {
    if (!m_settings) {
        m_settings = new Settings();
    }
    return m_settings;
}

const QString Settings::getLanguage() {
    return settings->value("language", "").toString();
}

void Settings::setLanguage(const QString & language) {
    settings->setValue("language", language);
}

Settings::Settings(QObject * parent) : QObject(parent) {
    this->settings = new QSettings("settings_conf", QSettings::IniFormat);
}
