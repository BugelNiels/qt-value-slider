#include "doubleslider.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QStyleOptionProgressBar>
#include <QElapsedTimer>
#include <utility>
#include <QApplication>

ValueSliders::DoubleSlider::DoubleSlider(QString name)
        : name_(std::move(name)) {
    init();
}

ValueSliders::DoubleSlider::DoubleSlider(QString name, double value)
        : name_(std::move(name)),
          value_(value) {
    init();
}


ValueSliders::DoubleSlider::DoubleSlider(QString name, double value, double min, double max, bool allowOutside)
        : allowOutside_(allowOutside),
          name_(std::move(name)),
          value_(value),
          min_(min),
          max_(max) {
    init();
}

void ValueSliders::DoubleSlider::init() {
    setFocusPolicy(Qt::StrongFocus);
    setMinimum(int(std::round(min_ * 100)));
    setMaximum(int(std::round(max_ * 100)));
    setValue(int(std::round(value_ * 100)));

    blinkerTimer_ = std::make_shared<QTimer>(this);
    connect(blinkerTimer_.get(), &QTimer::timeout, this, &ValueSliders::DoubleSlider::toggleBlinkerVisibility);
}

void ValueSliders::DoubleSlider::toggleBlinkerVisibility() {
    blinkerVisible_ = !blinkerVisible_;
    update();
}

QString ValueSliders::DoubleSlider::text() const {
    return "";
}

void ValueSliders::DoubleSlider::startTyping() {
    setFocus();
    QApplication::setOverrideCursor(Qt::BlankCursor);
    grabKeyboard();
    setEnabled(true);
    typeInput_ = "";
    typing_ = true;
    blinkerTimer_->start(blinkerInterval_);
    update();
}

void ValueSliders::DoubleSlider::stopTyping() {
    releaseKeyboard();
    QApplication::restoreOverrideCursor();
    blinkerTimer_->stop();
    typing_ = false;
    setVal(value_);
    update();
}

void ValueSliders::DoubleSlider::paintEvent(QPaintEvent *event) {
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

        painter.setPen(palette().color(QPalette::WindowText));
        QRect rect = style()->subElementRect(QStyle::SE_ProgressBarContents, &option, this);
        rect.setX(rect.x() + padding_);
        QString nameText = name_;
        painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, nameText);

        QString valueText = QString::number(value_, 'f', 3);
        QRect valueRect = rect.adjusted(QFontMetrics(font()).horizontalAdvance(nameText), 0, -padding_, 0);
        painter.drawText(valueRect, Qt::AlignRight | Qt::AlignVCenter, valueText);
    }

}

void ValueSliders::DoubleSlider::mousePressEvent(QMouseEvent *event) {
    setFocus();
    startPos_ = QCursor::pos();
    oldPos_ = event->pos().x();
    if (typing_) {
        submitTypedInput();
    }
    QApplication::setOverrideCursor(Qt::BlankCursor);
    mouseMoved_ = false;
    event->accept();
}

void ValueSliders::DoubleSlider::mouseMoveEvent(QMouseEvent *event) {
    if (typing_) {
        event->ignore();
        return;
    }
    if (event->buttons() & Qt::LeftButton) {
        int diff = event->pos().x() - oldPos_;
        QCursor::setPos(startPos_);
        updateValueByPosition(diff);
        mouseMoved_ = true;
        event->accept();
        return;
    }
}

void ValueSliders::DoubleSlider::mouseReleaseEvent(QMouseEvent *event) {
    QApplication::restoreOverrideCursor();
    QCursor::setPos(startPos_);
    if (typing_) {
        return;
    }
    if (mouseMoved_) {
        if (event->button() == Qt::LeftButton) {
            updateValueByPosition(event->pos().x() - oldPos_);
        }
    } else {
        startTyping();
    }
    event->accept();
}

void ValueSliders::DoubleSlider::updateValueByPosition(int x) {
    double ratio = static_cast<double>(x) / width();
    double val = ratio * (maximum() - minimum());
    setVal(value_ + val / 100.0f);
    setEnabled(true);
}

void ValueSliders::DoubleSlider::mouseDoubleClickEvent(QMouseEvent *event) {
    startTyping();
    event->accept();
}

void ValueSliders::DoubleSlider::keyPressEvent(QKeyEvent *event) {
    if (typing_) {
        event->accept();
        if (event->key() == Qt::Key_Escape) {
            stopTyping();
            setEnabled(true);
            return;
        }
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            submitTypedInput();
            return;
        }
        if (event->key() == Qt::Key_Backspace) {
            typeInput_.chop(1);
            update();
            return;
        }
        typeInput_ += event->text();
        update();
    }
}

void ValueSliders::DoubleSlider::submitTypedInput() {
    bool ok;
    double newVal = typeInput_.toDouble(&ok);
    if (ok) {
        setVal(newVal);
    }
    stopTyping();
    setEnabled(true);
}

void ValueSliders::DoubleSlider::focusOutEvent(QFocusEvent *event) {
    QWidget::focusOutEvent(event);
    if(typing_) {
        stopTyping();
    }
}

void ValueSliders::DoubleSlider::setVal(double value) {
    if (value_ == value) {
        return;
    }
    if (allowOutside_) {
        value_ = value;
    } else {
        value_ = std::clamp(value, min_, max_);
    }
    setValue(std::clamp(int(std::round(value * 100.0f)), minimum(), maximum()));
    update();
    emit valueChanged(int(std::round(value_ * 100.0f)));
}

double ValueSliders::DoubleSlider::getVal() const {
    return value_;
}

void ValueSliders::DoubleSlider::enterEvent(QEnterEvent *event) {
    QWidget::enterEvent(event);
    QApplication::setOverrideCursor(Qt::SizeHorCursor);
}

void ValueSliders::DoubleSlider::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    QApplication::restoreOverrideCursor();
}
