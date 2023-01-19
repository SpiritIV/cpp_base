cmake_minimum_required(VERSION 3.15)
project(app)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(${PROJECT_NAME} task_1.cpp) # add this executable

target_link_libraries(${PROJECT_NAME} PRIVATE gtest) # link google test to this executable