cmake_minimum_required(VERSION 3.12)
project(Puzzles)

set(CMAKE_CXX_STANDARD 17)

add_executable(Puzzles main.cpp board.cpp board.h solver.cpp solver.h)