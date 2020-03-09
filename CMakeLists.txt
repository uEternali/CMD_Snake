cmake_minimum_required(VERSION 3.0.0)

project(Snake🐍! VERSION 0.1.0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
include_directories(include)
set(SOURCES source/main.cpp source/screen.cpp source/snake.cpp source/scoreboard.cpp source/operationboard.cpp)
add_executable(Snake ${SOURCES})
