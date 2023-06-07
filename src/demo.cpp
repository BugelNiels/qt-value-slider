#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>

#include "decimalsliderwidget.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    QFont font("Lato");
    font.setPixelSize(14);
    QApplication::setFont(font);
    QMainWindow w;


    QWidget wrapper;
    QVBoxLayout layout;
    wrapper.setLayout(&layout);

    layout.addWidget(new QLabel("Example:"));
    layout.addWidget(new DecimalSliderWidget("Slider", 5, 0, 100));
    w.setCentralWidget(&wrapper);

    w.show();
    return QApplication::exec();
}