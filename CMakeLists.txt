cmake_minimum_required(VERSION 3.16)
project(grain_simulate)

set(CMAKE_CXX_STANDARD 14)

add_executable(grain_simulate src/main.cpp src/Calculator.cpp src/Calculator.h src/Simulator.cpp src/Simulator.h src/Simulator3D.cpp src/Simulator3D.h)