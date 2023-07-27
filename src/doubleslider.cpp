#include <doubleslider.hpp>

#include <QDebug>
#include <utility>

namespace ValueSliders {

DoubleSlider::DoubleSlider(QString name, double value) : ValueSlider(std::move(name), value) {
    updateBounds();
}

DoubleSlider::DoubleSlider(QString name, double value, double min, double max, BoundMode boundMode)
    : ValueSlider(std::move(name), value, min, max, boundMode) {
    updateBounds();
}

void DoubleSlider::updateBounds() {
    setMinimum(int(std::round(min_ * 100.0)));
    setMaximum(int(std::round(max_ * 100.0)));
    if (boundMode_ == BoundMode::UPPER_LOWER) {
        setValue(int(std::round(value_ * 100.0)));
    } else {
        setValue(minimum());
    }
    stepSize_ = (max_ - min_) / 100.0;
}

int DoubleSlider::transform(double val) const {
    return int(std::round(val * 100.0));
}

double DoubleSlider::convertString(const QString &string, bool &ok) {
    return string.toDouble(&ok);
}

QString DoubleSlider::createString(double val) const {
    return QString::number(val, 'f', 3);
}

void DoubleSlider::emitValueUpdated(double val) {
    emit valueUpdated(val);
}

double DoubleSlider::getValueByPosition(int x) {
    double val = x * stepSize_;
    return value_ + val;
}

} // namespace ValueSliders