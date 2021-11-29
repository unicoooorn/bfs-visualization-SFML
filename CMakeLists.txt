cmake_minimum_required(VERSION 3.20)
project(maze)

find_package(SFML 2.5 COMPONENTS graphics audio)

set(CMAKE_CXX_STANDARD 14)

add_executable(maze main.cpp Cell.cpp Cell.h Game.cpp Game.h true_random.h generator.h generator.cpp generatorhelper.h generatorhelper.cpp)

target_link_libraries(maze sfml-graphics sfml-audio)
