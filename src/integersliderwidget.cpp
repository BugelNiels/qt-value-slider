#include "integersliderwidget.hpp"
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

#include <utility>
#include <QStyleOptionProgressBar>

IntegerSliderWidget::IntegerSliderWidget(QString name)
        : name_(std::move(name)) {
    init();
}

IntegerSliderWidget::IntegerSliderWidget(QString name, int value)
        : name_(std::move(name)),
          value_(value) {
    init();
}


IntegerSliderWidget::IntegerSliderWidget(QString name, int value, int min, int max, bool allowOutside)
        : name_(std::move(name)),
          value_(value),
          min_(min),
          max_(max),
          allowOutside_(allowOutside) {
    init();
}

void IntegerSliderWidget::init() {
    setMinimum(min_);
    setMaximum(max_);
    setValue(value_);

    blinkerTimer_ = new QTimer(this);
    connect(blinkerTimer_, &QTimer::timeout, this, &IntegerSliderWidget::toggleBlinkerVisibility);
    oldBase_ = palette().color(QPalette::Base);
}

void IntegerSliderWidget::toggleBlinkerVisibility() {
    blinkerVisible_ = !blinkerVisible_;
    update();
}

QString IntegerSliderWidget::text() const {
    return "";
}

void IntegerSliderWidget::startTyping() {
    setFocus();
    select();
    setValue(minimum());
    typeInput_ = "";
    typing_ = true;
    blinkerTimer_->start(blinkerInterval_);
    update();
}

void IntegerSliderWidget::stopTyping() {
    blinkerTimer_->stop();
    typing_ = false;
    setValue(std::clamp(value_, minimum(), maximum()));
    unselect();
    update();
}

void IntegerSliderWidget::paintEvent(QPaintEvent *event) {
    QProgressBar::paintEvent(event);

    QPainter painter(this);
    QStyleOptionProgressBar option;
    initStyleOption(&option);
    if (typing_) {
        QRect rect = style()->subElementRect(QStyle::SE_ProgressBarContents, &option, this);
        rect.setX(rect.x() + padding_);

        bool start = typeInput_ == "";
        QFontMetrics fontMetrics(font());

        painter.save();
        QString nameText = start ? QString::number(value_) : typeInput_;
        QSize textSize = fontMetrics.size(Qt::TextSingleLine, nameText);

        QRect textRect = rect;
        textRect.setWidth(textSize.width() + padding_);
        textRect.moveLeft(padding_ / 2);
        QColor highlightColor = palette().color(QPalette::Highlight);

        painter.setBrush(QBrush(highlightColor));
        painter.setPen(Qt::NoPen);
        if (start) {
            painter.drawRect(textRect);
        }

        if (blinkerVisible_) {
            QRect blinkerRect(textRect.x() + textRect.width() - padding_ / 2, textRect.y(), 2, textRect.height());
            painter.fillRect(blinkerRect, palette().color(QPalette::WindowText));
        }

        painter.restore();

        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, nameText);
    } else {
        QRect rect = style()->subElementRect(QStyle::SE_ProgressBarContents, &option, this);
        rect.setX(rect.x() + padding_);
        QString nameText = name_;
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, nameText);

        QString valueText = QString::number(value_);
        QRect valueRect = rect.adjusted(QFontMetrics(font()).horizontalAdvance(nameText), 0, -padding_, 0);
        painter.drawText(valueRect, Qt::AlignRight | Qt::AlignVCenter, valueText);
    }

}

void IntegerSliderWidget::select() {
    QPalette curPalette = QProgressBar::palette();
    curPalette.setColor(QPalette::Base, palette().color(QPalette::AlternateBase));
    QProgressBar::setPalette(curPalette);
}

void IntegerSliderWidget::unselect() {
    QPalette curPalette = QProgressBar::palette();
    curPalette.setColor(QPalette::Base, oldBase_);
    QProgressBar::setPalette(curPalette);
}

void IntegerSliderWidget::mousePressEvent(QMouseEvent *event) {
    QProgressBar::mousePressEvent(event);
    setFocus();
    if (typing_) {
        stopTyping();
    }
    select();
    mouseMoved_ = false;
}

void IntegerSliderWidget::mouseMoveEvent(QMouseEvent *event) {
    QProgressBar::mouseMoveEvent(event);
    if (typing_) {
        return;
    }
    if (event->buttons() & Qt::LeftButton) {
        updateValueByPosition(event->pos().x());
        mouseMoved_ = true;
    }
}

void IntegerSliderWidget::mouseReleaseEvent(QMouseEvent *event) {
    QProgressBar::mouseReleaseEvent(event);
    if (typing_) {
        return;
    }
    if (mouseMoved_) {
        if (event->button() == Qt::LeftButton) {
            updateValueByPosition(event->pos().x());
            unselect();

        }
    } else {
        startTyping();
    }
}

void IntegerSliderWidget::updateValueByPosition(int x) {
    double ratio = static_cast<double>(x) / width();
    double val = minimum() + ratio * (maximum() - minimum());
    int newVal = int(std::round(val));
    setValue(newVal);
    if (allowOutside_) {
        value_ = newVal;
    } else {
        value_ = std::clamp(newVal, min_, max_);
    }
    update();
}

void IntegerSliderWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    startTyping();
}

void IntegerSliderWidget::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    if (typing_) {
        if (event->key() == Qt::Key_Escape) {
            stopTyping();
            return;
        }
        if (event->key() == Qt::Key_Return) {
            bool ok;
            double newVal = typeInput_.toDouble(&ok);
            if (ok) {
                int iNewVal = int(std::round(newVal));
                if(!allowOutside_) {
                    iNewVal = std::clamp(iNewVal, min_, max_);
                }
                value_ = iNewVal;
            }
            stopTyping();
            return;
        }
        typeInput_ += event->text();
        update();
    }
}

void IntegerSliderWidget::focusOutEvent(QFocusEvent *event) {
    QWidget::focusOutEvent(event);
    stopTyping();
}
