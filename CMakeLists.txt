cmake_minimum_required(VERSION 3.16)
project(grain_simulate)

set(CMAKE_CXX_STANDARD 14)

add_executable(MRCS src/main.cpp src/Calculator.cpp src/Calculator.h src/Simulator.cpp src/Simulator.h src/Simulator3D.cpp src/Simulator3D.h)
add_executable(DEMO2d src/Calculator.cpp src/Calculator.h src/Simulator.cpp src/Simulator.h src/Simulator3D.cpp src/Simulator3D.h demo/Demo2D.cpp)
add_executable(DEMO3d src/Calculator.cpp src/Calculator.h src/Simulator.cpp src/Simulator.h src/Simulator3D.cpp src/Simulator3D.h demo/Demo3D.cpp)
