cmake_minimum_required(VERSION 3.16)
project(valueSliders VERSION 1.0 LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

if (SLIDER_LIBRARY)
    add_library(${PROJECT_NAME}
            src/decimalsliderwidget.cpp
            src/integersliderwidget.cpp
            )
else ()
    add_executable(${PROJECT_NAME}
            src/decimalsliderwidget.cpp
            src/integersliderwidget.cpp
            src/demo.cpp
            )
endif ()

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        include/
        )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})