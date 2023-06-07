#pragma once

#include <QWidget>
#include <QProgressBar>
#include <QLineEdit>
#include <QElapsedTimer>

class DecimalSliderWidget : public QProgressBar {
public:
    DecimalSliderWidget() = default;

    explicit DecimalSliderWidget(QString name);

    DecimalSliderWidget(QString name, double value);

    DecimalSliderWidget(QString name, double value, double min, double max, bool allowOutside = false);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    [[nodiscard]] QString text() const override;

    void paintEvent(QPaintEvent *event) override;

    void focusOutEvent(QFocusEvent *event) override;

private:
    const int padding_ = 12;
    const int blinkerInterval_ = 500;

    QColor oldBase_;

    bool allowOutside_ = true;
    bool blinkerVisible_ = false;
    bool typing_ = false;
    QTimer *blinkerTimer_ = nullptr;
    QString typeInput_ = "";

    QString name_ = "value";
    double value_ = 0.5;
    double min_ = 0;
    double max_ = 1;

    void updateValueByPosition(int x);

    void init();

    void toggleBlinkerVisibility();

    void startTyping();

    void stopTyping();

    void select();

    void unselect();

    bool mouseMoved_ = false;
};
