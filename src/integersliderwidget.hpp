#pragma once

#include <QWidget>
#include <QProgressBar>
#include <QLineEdit>
#include <QElapsedTimer>

class IntegerSliderWidget : public QProgressBar {
public:
    IntegerSliderWidget() = default;

    explicit IntegerSliderWidget(QString name);

    IntegerSliderWidget(QString name, int value);

    IntegerSliderWidget(QString name, int value, int min, int max);

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

    bool blinkerVisible_ = false;
    bool typing_ = false;
    QTimer *blinkerTimer_ = nullptr;
    QString typeInput_ = "";

    QString name_ = "value";
    int value_ = 50;
    int min_ = 0;
    int max_ = 100;

    void updateValue(int x);

    void init();

    void toggleBlinkerVisibility();

    void startTyping();

    void stopTyping();

    void select();

    void unselect();

    bool mouseMoved_ = false;
};
