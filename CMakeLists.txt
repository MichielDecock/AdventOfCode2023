cmake_minimum_required(VERSION 3.25.3)

project(AOC VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(AOC src/main.cpp)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(AOC PRIVATE core)
