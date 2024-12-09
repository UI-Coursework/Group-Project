cmake_minimum_required(VERSION 3.16)

project(watertool VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts LinguistTools)

qt_standard_project_setup()

qt_add_executable(watertool
    main.cpp
    datamanager.cpp
    mainwindow.cpp
    overviewpage.cpp
    enviwindow.cpp
)
target_link_libraries(watertool PRIVATE Qt6::Widgets Qt6::Charts)

qt_add_translations(watertool TS_FILES watertool_de.ts watertool_fr.ts)

set_target_properties(watertool PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)
