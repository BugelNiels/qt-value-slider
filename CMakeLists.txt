cmake_minimum_required(VERSION 3.10)
project(QtValueSlider)

set(SOURCES
        src/decimalsliderwidget.cpp
        src/decimalsliderwidget.hpp
        )

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)

option(ENABLE_DEMO "Enable demo" OFF)

if(ENABLE_DEMO)
  set(DEMO_SOURCE src/demo.cpp)
  add_executable(Demo ${DEMO_SOURCE})
  target_link_libraries(Demo PRIVATE QtValueSlider)
endif()