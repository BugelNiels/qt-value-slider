#include "doubleslider.hpp"

#include <utility>
#include <QDebug>

ValueSliders::DoubleSlider::DoubleSlider(QString name, double value) : ValueSlider(std::move(name), value) {
    updateBounds();
}

ValueSliders::DoubleSlider::DoubleSlider(QString name, double value, double min, double max,
                                         ValueSliders::BoundMode boundMode) : ValueSlider(std::move(name), value, min,
                                                                                          max,
                                                                                          boundMode) {
    updateBounds();
}

void ValueSliders::DoubleSlider::updateBounds() {
    setMinimum(int(min_ * 100.0 + 0.5));
    setMaximum(int(max_ * 100.0 + 0.5));
    if(boundMode_ == BoundMode::UPPER_LOWER) {
        setValue(int(value_ * 100.0 + 0.5));
    } else {
        setValue(minimum());
    }
}

int ValueSliders::DoubleSlider::transform(double val) const {
    return int(val * 100.0 + 0.5);
}

double ValueSliders::DoubleSlider::convertString(const QString &string, bool &ok) {
    return string.toDouble(&ok);
}

QString ValueSliders::DoubleSlider::createString(double val) const {
    return QString::number(val, 'f', 3);
}

void ValueSliders::DoubleSlider::emitValueUpdated(double val) {
    emit valueUpdated(val);
}

void ValueSliders::DoubleSlider::emitEditEnded() {
    emit editEnded();
}

double ValueSliders::DoubleSlider::getValueByPosition(int x) {
    double ratio = static_cast<double>(x) / width();
    double val = ratio * (maximum() - minimum());
    return value_ + val / 100.0;
}
