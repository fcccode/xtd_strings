cmake_minimum_required(VERSION 3.3)

project(split)
find_package(xtd.strings REQUIRED)
add_executable(${PROJECT_NAME} src/split.cpp)
target_link_libraries(${PROJECT_NAME} xtd.strings)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "xtd.strings")
