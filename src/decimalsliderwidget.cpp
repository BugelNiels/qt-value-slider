#include "decimalsliderwidget.hpp"
#include <QMouseEvent>
#include <QPainter>

#include <utility>
#include <QStyleOptionProgressBar>

DecimalSliderWidget::DecimalSliderWidget(QString name)
        : name_(std::move(name)) {
}

DecimalSliderWidget::DecimalSliderWidget(QString name, double value)
        : name_(std::move(name)),
          value_(value) {
}


DecimalSliderWidget::DecimalSliderWidget(QString name, double value, double min, double max)
        : name_(std::move(name)),
          value_(value),
          min_(min),
          max_(max) {
}

QString DecimalSliderWidget::text() const {
    return "";
}

void DecimalSliderWidget::paintEvent(QPaintEvent *event) {
    QProgressBar::paintEvent(event);

    QPainter painter(this);
    QStyleOptionProgressBar option;
    initStyleOption(&option);
    QRect rect = style()->subElementRect(QStyle::SE_ProgressBarContents, &option, this);
    rect.setX(rect.x() + padding_);
    // Align name to the left
    QString nameText = name_;
    painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, nameText);

    // Align value to the right
    QString valueText = QString::number(value_, 'f', 2); // Adjust the precision as needed
    QRect valueRect = rect.adjusted(QFontMetrics(font()).horizontalAdvance(nameText), 0, -padding_, 0);
    painter.drawText(valueRect, Qt::AlignRight | Qt::AlignVCenter, valueText);
}

void DecimalSliderWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        updateValue(event->pos().x());
    }
    QProgressBar::mousePressEvent(event);
}

void DecimalSliderWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        updateValue(event->pos().x());
    }
    QProgressBar::mouseMoveEvent(event);
}

void DecimalSliderWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        updateValue(event->pos().x());
    }
    QProgressBar::mouseReleaseEvent(event);
}

void DecimalSliderWidget::updateValue(int x) {
    double ratio = static_cast<double>(x) / width();
    value_ = minimum() + ratio * (maximum() - minimum());
    setValue(value_);
}
