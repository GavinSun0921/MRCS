cmake_minimum_required(VERSION 3.16)
project(grain_simulate)

set(CMAKE_CXX_STANDARD 14)

add_executable(grain_simulate main.cpp Calculator.cpp Calculator.h Simulator.cpp Simulator.h Simulator3D.cpp Simulator3D.h)