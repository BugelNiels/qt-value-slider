#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "doubleslider.hpp"
#include "intslider.hpp"

int main(int argc, char* argv[]) {
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
    layout.addWidget(new ValueSliders::DoubleSlider("Double", 10.0));
    layout.addWidget(new ValueSliders::IntSlider("Integer", 10));

    layout.addWidget(new ValueSliders::DoubleSlider("Bounded Double", 50, 0, 100));
    layout.addWidget(new ValueSliders::IntSlider("Custom Name", 0, -50, 50));

    w.setCentralWidget(&wrapper);

    w.show();
    return QApplication::exec();
}
