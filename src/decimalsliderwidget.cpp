#include "decimalsliderwidget.hpp"

#include <utility>

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
