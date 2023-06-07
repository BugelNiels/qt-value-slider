#pragma once

#include <QWidget>

class DecimalSliderWidget : public QWidget {
public:
    DecimalSliderWidget() = default;

    explicit DecimalSliderWidget(QString name);

    DecimalSliderWidget(QString name, double value);

    DecimalSliderWidget(QString name, double value, double min, double max);

private:
    QString name_ = "value";
    double value_ = 0.5;
    double min_ = 0;
    double max_ = 1;
};
