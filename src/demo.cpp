#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>

#include "../include/decimalsliderwidget.hpp"
#include "../include/integersliderwidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFont font("Lato");
    font.setPixelSize(14);
    QApplication::setFont(font);
    QMainWindow w;
    w.setWindowTitle("Value Slider Demo");
    QWidget wrapper;
    QVBoxLayout layout;
    wrapper.setLayout(&layout);

    layout.addWidget(new QLabel("This is a small demo program:"));
    layout.addWidget(new ValueSliders::DecimalSliderWidget("Double"));
    layout.addWidget(new ValueSliders::IntegerSliderWidget("Integer"));

    layout.addWidget(new ValueSliders::DecimalSliderWidget("Bounded Double", 50, 0, 100, false));
    layout.addWidget(new ValueSliders::IntegerSliderWidget("Custom Name", 0, -50, 50, false));

    w.setCentralWidget(&wrapper);

    w.show();
    return QApplication::exec();
}