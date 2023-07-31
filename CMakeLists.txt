cmake_minimum_required(VERSION 3.9)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(SLIDER_LIBRARY ON)

project(valueSliders VERSION 1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
include(GNUInstallDirs)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets)

if (SLIDER_LIBRARY MATCHES ON)
    message("Building qt-value-sliders library")
    add_library(${PROJECT_NAME}
            include/doubleslider.hpp
            include/intslider.hpp
            include/valueslider.hpp
            src/doubleslider.cpp
            src/intslider.cpp
            src/valueslider.cpp
            )
else ()
    message("Building demo program")
    add_executable(${PROJECT_NAME}
            include/doubleslider.hpp
            include/intslider.hpp
            include/valueslider.hpp
            src/doubleslider.cpp
            src/intslider.cpp
            src/valueslider.cpp
            src/demo.cpp)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        include/
        )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
