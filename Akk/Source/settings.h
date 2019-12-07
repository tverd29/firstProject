#pragma once

#include <QSettings>

class Settings : public QObject {
    Q_OBJECT

  private:
    QSettings * settings = nullptr;
    static Settings * m_settings;

  public:
    static Settings * Instance();

    const QString getLanguage();
    void setLanguage(const QString & language);

  private:
    explicit Settings(QObject * parrent = nullptr);
    ~Settings() = default;
};
