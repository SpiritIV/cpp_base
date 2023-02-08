cmake_minimum_required(VERSION 3.6)

project(sbomber)

set(SRC_CPP src/Ground.cpp src/House.cpp src/LevelGUI.cpp src/MyTools.cpp src/Sbomber.cpp src/Tank.cpp src/DynamicObject.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SRC_CPP} SBomberProject.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)