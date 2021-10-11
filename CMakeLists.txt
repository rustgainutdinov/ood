cmake_minimum_required(VERSION 3.17)
project(ood)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lw1)

add_executable(SimUDuck lw1/SimUDuck/SimUDuck.cpp)
add_executable(SimUDuckFunc lw1/SimUDuckFunc/SimUDuckFunc.cpp)
add_executable(WeatherStation lw2/WeatherStation/main.cpp)
