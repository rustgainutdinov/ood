cmake_minimum_required(VERSION 3.20)
project(ood)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lw1)

add_executable(ood lw1/main.cpp)
