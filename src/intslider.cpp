#include "intslider.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QStyleOptionProgressBar>
#include <QElapsedTimer>
#include <utility>
#include <QApplication>

ValueSliders::IntSlider::IntSlider(QString name)
        : name_(std::move(name)) {
    init();
}

ValueSliders::IntSlider::IntSlider(QString name, int value)
        : name_(std::move(name)),
          value_(value) {
    init();
}


ValueSliders::IntSlider::IntSlider(QString name, int value, int min, int max, bool allowOutside)
        : allowOutside_(allowOutside),
          name_(std::move(name)),
          value_(value),
          min_(min),
          max_(max) {
    init();
}

void ValueSliders::IntSlider::init() {
    setFocusPolicy(Qt::StrongFocus);
    setMinimum(min_);
    setMaximum(max_);
    setValue(value_);

    blinkerTimer_ = std::make_shared<QTimer>(this);
    connect(blinkerTimer_.get(), &QTimer::timeout, this, &ValueSliders::IntSlider::toggleBlinkerVisibility);
}

void ValueSliders::IntSlider::toggleBlinkerVisibility() {
    blinkerVisible_ = !blinkerVisible_;
    update();
}

QString ValueSliders::IntSlider::text() const {
    return "";
}

void ValueSliders::IntSlider::startTyping() {
    setFocus();
    QApplication::setOverrideCursor(Qt::BlankCursor);
    grabKeyboard();
    setEnabled(true);
    typeInput_ = "";
    typing_ = true;
    blinkerTimer_->start(blinkerInterval_);
    update();
}

void ValueSliders::IntSlider::stopTyping() {
    releaseKeyboard();
    QApplication::restoreOverrideCursor();
    blinkerTimer_->stop();
    typing_ = false;
    setVal(value_);
    update();
}

void ValueSliders::IntSlider::paintEvent(QPaintEvent *event) {
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

void ValueSliders::IntSlider::mousePressEvent(QMouseEvent *event) {
    setFocus();
    startPos_ = QCursor::pos();
    oldPos_ = event->pos().x();
    if (typing_) {
        submitTypedInput();
    }
    moveValue_ = value_;
    QApplication::setOverrideCursor(Qt::BlankCursor);
    mouseMoved_ = false;
    event->accept();
}

void ValueSliders::IntSlider::mouseMoveEvent(QMouseEvent *event) {
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

void ValueSliders::IntSlider::mouseReleaseEvent(QMouseEvent *event) {
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

void ValueSliders::IntSlider::updateValueByPosition(int x) {
    double ratio = static_cast<double>(x) / width();
    double val = ratio * (maximum() - minimum());
    moveValue_ = moveValue_ + val;
    setVal(int(std::round(moveValue_)));
    setEnabled(true);
}

void ValueSliders::IntSlider::mouseDoubleClickEvent(QMouseEvent *event) {
    startTyping();
    event->accept();
}

void ValueSliders::IntSlider::keyPressEvent(QKeyEvent *event) {
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

void ValueSliders::IntSlider::submitTypedInput() {
    bool ok;
    double newVal = typeInput_.toDouble(&ok);
    if (ok) {
        setVal(int(round(newVal)));
    }
    stopTyping();
    setEnabled(true);
}

void ValueSliders::IntSlider::focusOutEvent(QFocusEvent *event) {
    QWidget::focusOutEvent(event);
    if(typing_) {
        stopTyping();
    }
}

void ValueSliders::IntSlider::setVal(int value) {
    if (value_ == value) {
        return;
    }
    if (allowOutside_) {
        value_ = value;
    } else {
        value_ = std::clamp(value, min_, max_);
    }
    setValue(std::clamp(value, minimum(), maximum()));
    update();
    emit valueChanged(value_);
}

int ValueSliders::IntSlider::getVal() const {
    return value_;
}

void ValueSliders::IntSlider::enterEvent(QEnterEvent *event) {
    QWidget::enterEvent(event);
    QApplication::setOverrideCursor(Qt::SizeHorCursor);
}

void ValueSliders::IntSlider::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    QApplication::restoreOverrideCursor();
}
