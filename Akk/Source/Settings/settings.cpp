#include "settings.h"

Settings * Settings::m_settings = nullptr;

Settings * Settings::Instance() {
    if (!m_settings) {
        m_settings = new Settings();
    }
    return m_settings;
}

const QString Settings::getLanguage() {
    return settings->value("language", QVariant()).toString();
}

void Settings::setLanguage(const QString & language) {
    settings->setValue("language", language);
}

const QString Settings::getDefaultFile() {
    return settings->value("defaultFile", QVariant()).toString();
}

void Settings::setDefaultFile(const QString & file) {
    settings->setValue("defaultFile", file);
}

Settings::Settings(QObject * parent) : QObject(parent) {
    this->settings = new QSettings("settings_conf", QSettings::IniFormat);
}
