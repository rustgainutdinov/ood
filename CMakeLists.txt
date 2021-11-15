cmake_minimum_required(VERSION 3.17)
project(ood)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lw1)
include_directories(lw4)

# lw1
add_executable(SimUDuck lw1/SimUDuck/SimUDuck.cpp)
add_executable(SimUDuckFunc lw1/SimUDuckFunc/SimUDuckFunc.cpp)

# lw2
add_executable(WeatherStation lw2/WeatherStation/main.cpp)
add_executable(SetErase examples/set_erase.cpp)
add_executable(WeatherStationTests lw2/WeatherStation/test.cpp)
target_link_libraries(WeatherStationTests gtest_main)
add_test(NAME WeatherStationTests COMMAND WeatherStationTests)

# lw3
include_directories("${PROJECT_SOURCE_DIR}/lw3/")
add_executable(Coffee lw3/coffee/main.cpp)
add_executable(Streams lw3/streams/main.cpp)
add_executable(StreamsTests lw3/streams/test.cpp)
target_link_libraries(StreamsTests gtest_main)
add_test(NAME StreamsTests COMMAND StreamsTests)

add_executable(Painting lw4/painting/main.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#OPENCV
FetchContent_Declare(
        opencv
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_TAG        4.4.0
)
FetchContent_GetProperties(opencv)
if (NOT opencv_POPULATED)
    FetchContent_Populate(opencv)
endif ()
FetchContent_MakeAvailable(opencv)

# Find on pc
set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)

target_link_libraries(Painting ${OpenCV_LIBS})
add_executable(PaintingTests lw4/painting/test.cpp)
target_link_libraries(PaintingTests gtest_main)
target_link_libraries(PaintingTests ${OpenCV_LIBS})
add_test(NAME PaintingTests COMMAND PaintingTests)