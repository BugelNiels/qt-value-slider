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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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

#include "valueslider.hpp"
#include <QProgressBar>

namespace ValueSliders {

class DoubleSlider : public ValueSlider<double> {
    Q_OBJECT
  public:
    DoubleSlider(QString name, double value);

    DoubleSlider(QString name, double value, double min, double max, BoundMode boundMode = BoundMode::UPPER_LOWER);

    [[nodiscard]] int transform(double val) const override;

    double convertString(const QString& string, bool& ok) override;

    [[nodiscard]] QString createString(double val) const override;

    void emitValueUpdated(double val) override;

    void emitEditEnded() override;

    [[nodiscard]] double getValueByPosition(int x) override;

  Q_SIGNALS:

    void valueUpdated(double value);

    void editEnded();

  private:
    void updateBounds();
};
}  // namespace ValueSliders
