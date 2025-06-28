/**
 * MIT License
 *
 * Copyright (c) 2023 Niels Bugel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include <QProgressBar>

namespace ValueSliders {

    enum class BoundMode {
        UNCHECKED,
        UPPER_ONLY,
        LOWER_ONLY,
        UPPER_LOWER
    };

    template<class T>
    class ValueSlider : public QProgressBar {
    public:
        ValueSlider(QString name, T value);

        ValueSlider(QString name, T value, T min, T max, BoundMode boundMode);

        ~ValueSlider() override;

        void setVal(T value);

        [[nodiscard]] T getVal() const;

        [[nodiscard]] T boundVal(T value) const;

    protected:

        void mouseDoubleClickEvent(QMouseEvent *event) override;

        void mousePressEvent(QMouseEvent *event) override;

        void mouseMoveEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

        void keyPressEvent(QKeyEvent *event) override;

        [[nodiscard]] QString text() const override;

        void paintEvent(QPaintEvent *event) override;

        void focusOutEvent(QFocusEvent *event) override;

        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        void enterEvent(QEnterEvent *event) override;
        #else
        void enterEvent(QEvent *event) override;
        #endif

        void leaveEvent(QEvent *event) override;

        virtual int transform(T val) const = 0;

        virtual T convertString(const QString &string, bool &ok) = 0;

        virtual QString createString(T val) const = 0;

        virtual void emitValueUpdated(T val) = 0;

        virtual void emitEditEnded() = 0;      
      
        virtual T getValueByPosition(int x) = 0;

    protected:
        T value_;
        T min_;
        T max_;
        BoundMode boundMode_ = BoundMode::UNCHECKED;

    private:
        const int padding_ = 12;
        const int blinkerInterval_ = 500;

        // This determines how "fine" is the tuning. If the constant
        // equals 64 for example, the slider tick is 64th times
        // smaller.
        const int fineTuningThreshold_ = 64;

        bool blinkerVisible_ = false;
        bool typing_ = false;
        bool mouseMoved_ = false;
        int oldPos_;
        QPoint startPos_;
        int pendingDiff_ = 0;
        std::shared_ptr<QTimer> blinkerTimer_ = nullptr;
        QString typeInput_ = "";
        QString name_ = "value";

        void updateValueByPosition(int x);

        void init();

        void toggleBlinkerVisibility();

        void startTyping();

        void stopTyping();

        void submitTypedInput();

        [[nodiscard]] int getXPosByVal() const;

        bool slidingHover_ = false;
    };
} // ValueSliders
