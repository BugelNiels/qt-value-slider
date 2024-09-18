cmake_minimum_required(VERSION 3.9)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(SLIDER_LIBRARY ON)

project(valueSliders VERSION 1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)

if (SLIDER_LIBRARY MATCHES ON)
    add_library(${PROJECT_NAME}
            include/doubleslider.hpp
            include/intslider.hpp
            include/valueslider.hpp
            src/doubleslider.cpp
            src/intslider.cpp
            src/valueslider.cpp
            )
else ()
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
        Qt::Core
        Qt::Widgets
        )

if (SLIDER_LIBRARY MATCHES ON)
   target_include_directories(${PROJECT_NAME}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
        include/
        )
else ()
   target_include_directories(${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
        include/
        )
endif ()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
