cmake_minimum_required(VERSION 3.16)
project(valueSlider VERSION 1.0 LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

set(SRC_FILES
        src/decimalsliderwidget.cpp
        src/integersliderwidget.cpp
        src/decimalsliderwidget.hpp
        src/integersliderwidget.hpp
        )

if(NOT SLIDER_LIBRARY)
    list(APPEND SRC_FILES src/demo.cpp)
endif()

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
        ${SRC_FILES}
        )

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt::Core
        Qt::Widgets
        )

install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )