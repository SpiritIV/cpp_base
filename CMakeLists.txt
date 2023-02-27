cmake_minimum_required(VERSION 3.6)

project(sbomber)

set(SRC_CPP src/AnimateScrolling.cpp src/Bomb.cpp src/Ground.cpp src/House.cpp src/LevelGUI.cpp src/MyTools.cpp src/Plane.cpp src/SBomber.cpp src/Tank.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_CPP} SBomberProject.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)