#include <QApplication>
#include <QMainWindow>

#include "decimalsliderwidget.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    QFont font("Lato");
    font.setPixelSize(14);
    QApplication::setFont(font);
    QMainWindow w;

    w.setCentralWidget(new DecimalSliderWidget("Slider", 5, 0, 100));

    w.show();
    return QApplication::exec();
}