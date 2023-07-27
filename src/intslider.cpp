#include <intslider.hpp>

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionProgressBar>
#include <QTimer>

namespace ValueSliders {

IntSlider::IntSlider(QString name, int value) : ValueSlider(std::move(name), value) {
    updateBounds();
}

IntSlider::IntSlider(QString name, int value, int min, int max, BoundMode boundMode)
    : ValueSlider(std::move(name), value, min, max, boundMode) {
    updateBounds();
}

void IntSlider::updateBounds() {

    setMinimum(min_);
    setMaximum(max_);
    if (boundMode_ == BoundMode::UPPER_LOWER) {
        setValue(value_);
    } else {
        setValue(minimum());
    }
    stepSize_ = 1;
}

int IntSlider::transform(int val) const {
    return val;
}

int IntSlider::convertString(const QString &string, bool &ok) {
    return string.toInt(&ok);
}

QString IntSlider::createString(int val) const {
    return QString::number(val);
}

void IntSlider::emitValueUpdated(int val) {
    emit valueUpdated(val);
}

int IntSlider::getValueByPosition(int x) {
    double ratio = static_cast<double>(x) / width();
    double val = ratio * (maximum() - minimum());
    moveValue_ += val;
    switch (boundMode_) {
        case BoundMode::LOWER_ONLY:
            moveValue_ = std::max(moveValue_, double(min_) - 1.0);
            break;
        case BoundMode::UPPER_ONLY:
            moveValue_ = std::min(moveValue_, double(max_) - 1.0);
            break;
        case BoundMode::UPPER_LOWER:
            moveValue_ = std::clamp(moveValue_, double(min_) - 1.0, double(max_) + 1.0);
            break;
        default:
            break;
    }
    return int(std::round(moveValue_));
}

void IntSlider::mousePressEvent(QMouseEvent *event) {
    ValueSlider::mousePressEvent(event);
    moveValue_ = value_;
}

} // namespace ValueSliders