#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include <doubleslider.hpp>
#include <intslider.hpp>

using namespace ValueSliders;

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

    layout.addWidget(new QLabel("These sliders are bounded:"));
    layout.addWidget(new DoubleSlider("Double", 0.5, 0, 1, BoundMode::UPPER_LOWER));
    layout.addWidget(new IntSlider("Integer", 20, 0, 100, BoundMode::UPPER_LOWER));


    layout.addWidget(new QLabel("These sliders are unbounded:"));

    layout.addWidget(new DoubleSlider("Bounded Double", 50, 0, 100, BoundMode::UNCHECKED));
    layout.addWidget(new IntSlider("Custom Name", 0, -50, 50, BoundMode::UNCHECKED));

    w.setCentralWidget(&wrapper);

    w.show();
    return QApplication::exec();
}
