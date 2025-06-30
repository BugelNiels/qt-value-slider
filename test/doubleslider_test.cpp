#include "doubleslider.hpp"
#include <QApplication>
#include <gtest/gtest.h>

TEST(DoubleSliderTest, ConstructorDefaultPositive) {
    double val = 10.0;
    ValueSliders::DoubleSlider slider("Test Slider", val);
    EXPECT_DOUBLE_EQ(slider.getVal(), val);
    EXPECT_DOUBLE_EQ(slider.minimum(), 0.0);
    EXPECT_DOUBLE_EQ(slider.maximum(), 2 * val * 100);
}

TEST(DoubleSliderTest, ConstructorDefaultNegative) {
    double val = -10.0;
    ValueSliders::DoubleSlider slider("Test Slider", val);
    EXPECT_DOUBLE_EQ(slider.getVal(), val);
    EXPECT_DOUBLE_EQ(slider.minimum(), 2 * val * 100);
    EXPECT_DOUBLE_EQ(slider.maximum(), 0.0);
}

TEST(DoubleSliderTest, ConstructorDefaultZero) {
    ValueSliders::DoubleSlider slider("Test Slider", 0.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 0.0);
    EXPECT_DOUBLE_EQ(slider.minimum(), -100.0);
    EXPECT_DOUBLE_EQ(slider.maximum(), 100.0);
}

TEST(DoubleSliderTest, ConstructorBound) {
    double val = 10.0;
    double min = -5.0;
    double max = 30.0;
    ValueSliders::DoubleSlider slider("Test Slider", val, min, max);
    EXPECT_DOUBLE_EQ(slider.getVal(), val);
    EXPECT_DOUBLE_EQ(slider.minimum(), min * 100);
    EXPECT_DOUBLE_EQ(slider.maximum(), max * 100);
}

TEST(DoubleSliderTest, ConstructorBoundMustBeValid) {
    EXPECT_THROW(ValueSliders::DoubleSlider slider("Test Slider", 10.0, 10.0, 0.0), std::invalid_argument);
}

TEST(DoubleSliderTest, SetValWithinBoundsUpperLower) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UPPER_LOWER);
    slider.setVal(15.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 15.0);
}

TEST(DoubleSliderTest, SetValOutOfLowerBoundUpperLower) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UPPER_LOWER);
    slider.setVal(-5.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 0.0);
}

TEST(DoubleSliderTest, SetValOutOfUpperBoundUpperLower) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UPPER_LOWER);
    slider.setVal(25.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 20.0);
}

TEST(DoubleSliderTest, SetValWithinBoundsUpperOnly) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UPPER_ONLY);
    slider.setVal(15.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 15.0);
}

TEST(DoubleSliderTest, SetValOutOfLowerBoundUpperOnly) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UPPER_ONLY);
    slider.setVal(-5.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), -5.0);
}

TEST(DoubleSliderTest, SetValOutOfUpperBoundUpperOnly) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UPPER_ONLY);
    slider.setVal(25.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 20.0);
}

TEST(DoubleSliderTest, SetValWithinBoundsLowerOnly) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::LOWER_ONLY);
    slider.setVal(15.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 15.0);
}

TEST(DoubleSliderTest, SetValOutOfLowerBoundLowerOnly) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::LOWER_ONLY);
    slider.setVal(-5.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 0.0);
}

TEST(DoubleSliderTest, SetValOutOfUpperBoundLowerOnly) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::LOWER_ONLY);
    slider.setVal(25.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 25.0);
}

TEST(DoubleSliderTest, SetValWithinBoundsUnchecked) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UNCHECKED);
    slider.setVal(15.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 15.0);
}

TEST(DoubleSliderTest, SetValOutOfLowerBoundUnchecked) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UNCHECKED);
    slider.setVal(-5.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), -5.0);
}

TEST(DoubleSliderTest, SetValOutOfUpperBoundUnchecked) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UNCHECKED);
    slider.setVal(25.0);
    EXPECT_DOUBLE_EQ(slider.getVal(), 25.0);
}

TEST(DoubleSliderTest, TransformReturnsSameValue) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UNCHECKED);
    EXPECT_DOUBLE_EQ(slider.transform(0), 0);
    EXPECT_DOUBLE_EQ(slider.transform(1), 100);
    EXPECT_DOUBLE_EQ(slider.transform(25.0), 2500.0);
    EXPECT_DOUBLE_EQ(slider.transform(-25.0), -2500.0);
}

TEST(DoubleSliderTest, ConvertStringToDouble) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UNCHECKED);
    bool ok;
    EXPECT_DOUBLE_EQ(slider.convertString("15.5", ok), 15.5);
    EXPECT_TRUE(ok);

    EXPECT_DOUBLE_EQ(slider.convertString("-5.5", ok), -5.5);
    EXPECT_TRUE(ok);

    EXPECT_DOUBLE_EQ(slider.convertString("abc", ok),
                     0.0);  // Assuming it returns 0 for invalid input
    EXPECT_FALSE(ok);
}

TEST(DoubleSliderTest, CreateStringFromDouble) {
    ValueSliders::DoubleSlider slider("Test Slider", 10.0, 0.0, 20.0, ValueSliders::BoundMode::UNCHECKED);
    EXPECT_EQ(slider.createString(10.0), "10.000");
    EXPECT_EQ(slider.createString(-5.5), "-5.500");
    EXPECT_EQ(slider.createString(0.0), "0.000");
}
