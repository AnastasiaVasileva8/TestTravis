cmake_minimum_required(VERSION 2.6)
project(Calcapp)

add_executable(Calcapp calc.cpp)

target_link_libraries(Calcapp pthread)
