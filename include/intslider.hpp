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

    class IntSlider : public QProgressBar {
    public:
        IntSlider() = default;

        explicit IntSlider(QString name);

        IntSlider(QString name, int value);

        IntSlider(QString name, int value, int min, int max, bool allowOutside = false);

        void setVal(int value);

        [[nodiscard]] int getVal() const;

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


        bool allowOutside_ = true;
        bool blinkerVisible_ = false;
        bool typing_ = false;
        bool mouseMoved_ = false;
        std::shared_ptr<QTimer> blinkerTimer_ = nullptr;
        QString typeInput_ = "";
        QColor oldBase_;

        QString name_ = "value";
        int value_ = 50;
        int min_ = 0;
        int max_ = 100;

        void updateValueByPosition(int x);

        void init();

        void toggleBlinkerVisibility();

        void startTyping();

        void stopTyping();

        void select();

        void unselect();

    };
} // ValueSliders