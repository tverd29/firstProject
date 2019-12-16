#include "Popup.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QPainter>
#include <QPoint>

Popup * Popup::m_instance = nullptr;

Popup * Popup::Instance() {
    if (!m_instance) {
        m_instance = new Popup();
    }
    return m_instance;
}

void Popup::updateGeometry() {
    needCorrection = false;

    QPoint topLeft;
    topLeft.setX(this->center.x() - (width() / 2));
    topLeft.setY(this->center.y());

    QRect rect(topLeft, topLeft);
    setGeometry(rect);
}

void Popup::updateCenter(const QPoint center) {
    this->center = center;
    this->updateGeometry();
}

Popup::Popup(QWidget * parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint |  // Отключаем оформление окна
                   Qt::Tool |  // Отменяем показ в качестве отдельного окна
                   Qt::WindowStaysOnTopHint);  // Устанавливаем поверх всех окон
    setAttribute(Qt::WA_TranslucentBackground);  // Указываем, что фон будет прозрачным
    setAttribute(
        Qt::WA_ShowWithoutActivating);  // При показе, виджет не получается фокуса автоматически

    animation.setTargetObject(this);  // Устанавливаем целевой объект анимации
    animation.setPropertyName("popupOpacity");  // Устанавливаем анимируемое свойство
    connect(&animation, &QAbstractAnimation::finished, this,
            &Popup::hide);  // Подключаем сигнал окончания анимации к слоты скрытия

    // Настройка текста уведомления
    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // Устанавливаем по центру
    // И настраиваем стили
    label.setStyleSheet(
        "QLabel { color : white; "
        "margin-top: 6px;"
        "margin-bottom: 6px;"
        "margin-left: 10px;"
        "margin-right: 10px; }");

    // Производим установку текста в размещение, ...
    layout.addWidget(&label, 0, 0);
    setLayout(&layout);  // которое помещаем в виджет

    // По сигналу таймера будет произведено скрытие уведомления, если оно видимо
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Popup::hideAnimation);
}

void Popup::paintEvent(QPaintEvent * event) {
    Q_UNUSED(event)

    // А теперь настраиваем фон уведомления,который является прямоугольником с чёрным фоном
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Включаем сглаживание

    // Подготавливаем фон. rect() возвращает внутреннюю геометрию виджета уведомления, по
    // содержимому
    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    // Кисть настраиваем на чёрный цвет в режиме полупрозрачности
    painter.setBrush(QBrush(QColor(60, 60, 60, 200)));
    painter.setPen(Qt::NoPen);  // Край уведомления не будет выделен

    // Отрисовываем фон с закруглением краёв
    painter.drawRoundedRect(roundedRect, 15, 15);
}

void Popup::setPopupText(const QString & text) {
    if (text != label.text()) {
        needCorrection = true;
    }

    label.setText(text);  // Устанавливаем текст в Label
    adjustSize();         // С пересчётом размеров уведомления
}

void Popup::show() {
    setWindowOpacity(0.0);  // Устанавливаем прозрачность в ноль

    animation.setDuration(200);  // Настраиваем длительность анимации
    animation.setStartValue(0.0);  // Стартовое значение будет 0 (полностью прозрачный виджет)
    animation.setEndValue(1.0);  // Конечное - полностью непрозрачный виджет

    if (needCorrection) {
        this->updateGeometry();
    }

    QWidget::show();  // Отображаем виджет, который полностью прозрачен

    animation.start();   // И запускаем анимацию
    timer->start(1000);  // А также стартуем таймер, который запустит скрытие уведомления
}

void Popup::hideAnimation() {
    timer->stop();               // Останавливаем таймер
    animation.setDuration(500);  // Настраиваем длительность анимации
    animation.setStartValue(1.0);  // Стартовое значение будет 1 (полностью непрозрачный виджет)
    animation.setEndValue(0.0);  // Конечное - полностью прозрачный виджет
    animation.start();           // И запускаем анимацию
}

void Popup::hide() {
    // Если виджет прозрачный, то скрываем его
    if (qFuzzyCompare(getPopupOpacity(), 0.0)) {
        QWidget::hide();
    }
}

void Popup::setPopupOpacity(double opacity) {
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

double Popup::getPopupOpacity() const {
    return popupOpacity;
}
