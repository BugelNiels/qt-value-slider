#include "intslider.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QStyleOptionProgressBar>
#include <QApplication>

ValueSliders::IntSlider::IntSlider(QString name, int value) : ValueSlider(std::move(name), value) {
    updateBounds();
}

ValueSliders::IntSlider::IntSlider(QString name, int value, int bound, ValueSliders::BoundMode boundMode)
        : ValueSlider(std::move(name), value, bound, boundMode) {
    updateBounds();
}

ValueSliders::IntSlider::IntSlider(QString name, int value, int min, int max,
                                   ValueSliders::BoundMode boundMode) : ValueSlider(std::move(name), value, min,
                                                                                    max,
                                                                                    boundMode) {
    updateBounds();
}

void ValueSliders::IntSlider::updateBounds() {

    setMinimum(min_);
    setMaximum(max_);
    setValue(value_);
}


int ValueSliders::IntSlider::transform(int val) const {
    return val;
}

int ValueSliders::IntSlider::convertString(const QString &string, bool &ok) {
    return string.toInt(&ok);
}

QString ValueSliders::IntSlider::createString(int val) const {
    return QString::number(val);
}

void ValueSliders::IntSlider::emitValueUpdated(int val) {
    emit valueUpdated(val);
}

int ValueSliders::IntSlider::getValueByPosition(int x) {
    double ratio = static_cast<double>(x) / width();
    double val = ratio * (maximum() - minimum());
    moveValue_ += val;
    return int(std::round(moveValue_));
}

void ValueSliders::IntSlider::mousePressEvent(QMouseEvent *event) {
    ValueSlider::mousePressEvent(event);
    moveValue_ = value_;
}
