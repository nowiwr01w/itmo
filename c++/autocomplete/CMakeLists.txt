cmake_minimum_required(VERSION 3.12)
project(Autocomplete)

set(CMAKE_CXX_STANDARD 17)

add_executable(Autocomplete main.cpp term.cpp term.h binary_search_deluxe.h autocomplete.cpp autocomplete.h)