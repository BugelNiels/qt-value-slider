#pragma once

#include <QWidget>
#include <QProgressBar>
#include <QLineEdit>

class DecimalSliderWidget : public QProgressBar {
public:
    DecimalSliderWidget() = default;

    explicit DecimalSliderWidget(QString name);

    DecimalSliderWidget(QString name, double value);

    DecimalSliderWidget(QString name, double value, double min, double max);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    QString text() const override;
    void paintEvent(QPaintEvent *event) override;

private:

    const int padding_ = 15;

    QLineEdit* editor_;
    QString name_ = "value";
    double value_ = 0.5;
    double min_ = 0;
    double max_ = 1;


    void updateValue(int x);
};
