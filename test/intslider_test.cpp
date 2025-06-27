#include "intslider.hpp"
#include <QApplication>
#include <gtest/gtest.h>

TEST(IntSliderTest, ConstructorDefaultPositive) {
    int val = 10;
    ValueSliders::IntSlider slider("Test Slider", 10);
    EXPECT_EQ(slider.getVal(), val);
    EXPECT_EQ(slider.minimum(), 0);
    EXPECT_EQ(slider.maximum(), 2 * val);
}

TEST(IntSliderTest, ConstructorDefaultNegative) {
    int val = -10;
    ValueSliders::IntSlider slider("Test Slider", -10);
    EXPECT_EQ(slider.getVal(), val);
    EXPECT_EQ(slider.minimum(), 2 * val);
    EXPECT_EQ(slider.maximum(), 0);
}

TEST(IntSliderTest, ConstructorDefaultZero) {
    ValueSliders::IntSlider slider("Test Slider", 0);
    EXPECT_EQ(slider.getVal(), 0);
    EXPECT_EQ(slider.minimum(), -1);
    EXPECT_EQ(slider.maximum(), 1);
}

TEST(IntSliderTest, ConstructorBound) {
    int val = 10;
    int min = -5;
    int max = 30;
    ValueSliders::IntSlider slider("Test Slider", 10, min, max);
    EXPECT_EQ(slider.getVal(), val);
    EXPECT_EQ(slider.minimum(), min);
    EXPECT_EQ(slider.maximum(), max);
}

TEST(IntSliderTest, ConstructorBoundMustBeValid) {
    EXPECT_THROW(ValueSliders::IntSlider slider("Test Slider", 10, 10, 0), std::invalid_argument);
}

TEST(IntSliderTest, SetValWithinBoundsUpperLower) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UPPER_LOWER);
    slider.setVal(15);
    EXPECT_EQ(slider.getVal(), 15);
}

TEST(IntSliderTest, SetValOutOfLowerBoundUpperLower) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UPPER_LOWER);
    slider.setVal(-5);
    EXPECT_EQ(slider.getVal(), 0);
}

TEST(IntSliderTest, SetValOutOfUpperBoundUpperLower) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UPPER_LOWER);
    slider.setVal(25);
    EXPECT_EQ(slider.getVal(), 20);
}

TEST(IntSliderTest, SetValWithinBoundsUpperOnly) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UPPER_ONLY);
    slider.setVal(15);
    EXPECT_EQ(slider.getVal(), 15);
}

TEST(IntSliderTest, SetValOutOfLowerBoundUpperOnly) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UPPER_ONLY);
    slider.setVal(-5);
    EXPECT_EQ(slider.getVal(), -5);
}

TEST(IntSliderTest, SetValOutOfUpperBoundUpperOnly) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UPPER_ONLY);
    slider.setVal(25);
    EXPECT_EQ(slider.getVal(), 20);
}

TEST(IntSliderTest, SetValWithinBoundsLowerOnly) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::LOWER_ONLY);
    slider.setVal(15);
    EXPECT_EQ(slider.getVal(), 15);
}

TEST(IntSliderTest, SetValOutOfLowerBoundLowerOnly) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::LOWER_ONLY);
    slider.setVal(-5);
    EXPECT_EQ(slider.getVal(), 0);
}

TEST(IntSliderTest, SetValOutOfUpperBoundLowerOnly) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::LOWER_ONLY);
    slider.setVal(25);
    EXPECT_EQ(slider.getVal(), 25);
}

TEST(IntSliderTest, SetValWithinBoundsUnchecked) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UNCHECKED);
    slider.setVal(15);
    EXPECT_EQ(slider.getVal(), 15);
}

TEST(IntSliderTest, SetValOutOfLowerBoundUnchecked) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UNCHECKED);
    slider.setVal(-5);
    EXPECT_EQ(slider.getVal(), -5);
}

TEST(IntSliderTest, SetValOutOfUpperBoundUnchecked) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UNCHECKED);
    slider.setVal(25);
    EXPECT_EQ(slider.getVal(), 25);
}

TEST(IntSliderTest, TransformReturnsSameValue) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UNCHECKED);
    EXPECT_EQ(slider.transform(10), 10);
    EXPECT_EQ(slider.transform(-5), -5);
    EXPECT_EQ(slider.transform(25), 25);
}

TEST(IntSliderTest, ConvertStringToInt) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UNCHECKED);
    bool ok;
    EXPECT_EQ(slider.convertString("15", ok), 15);
    EXPECT_TRUE(ok);

    EXPECT_EQ(slider.convertString("-5", ok), -5);
    EXPECT_TRUE(ok);

    EXPECT_EQ(slider.convertString("abc", ok), 0);
    EXPECT_FALSE(ok);
}

TEST(IntSliderTest, CreateStringFromInt) {
    ValueSliders::IntSlider slider("Test Slider", 10, 0, 20, ValueSliders::BoundMode::UNCHECKED);
    EXPECT_EQ(slider.createString(10), "10");
    EXPECT_EQ(slider.createString(-5), "-5");
    EXPECT_EQ(slider.createString(0), "0");
}
