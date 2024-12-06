cmake_minimum_required(VERSION 3.16) 
project(cwk3 VERSION 1.0.0 LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17) 

set(CMAKE_CXX_STANDARD_REQUIRED ON) 

 

find_package(Qt6 REQUIRED COMPONENTS Widgets) 

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts) 

qt_standard_project_setup() 

 

qt_add_executable(watertool 
main.cpp 

datamanager.cpp 

# dataset.cpp 

# model.cpp 

mainwindow.cpp 

overviewpage.cpp 

enviwindow.cpp 

) 

 

target_link_libraries(watertool PRIVATE Qt6::Widgets) 

target_link_libraries(watertool PRIVATE Qt6::Widgets Qt6::Charts) 

 

# add_custom_command( TARGET watertool POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/new/data.csv $<TARGET_FILE_DIR:watertool> )  

# configure_file(Y-2024.csv ${CMAKE_BINARY_DIR}/Y-2024.csv COPYONLY)  

 

set_target_properties(watertool PROPERTIES 

WIN32_EXECUTABLE ON 

MACOSX_BUNDLE OFF 

) 
