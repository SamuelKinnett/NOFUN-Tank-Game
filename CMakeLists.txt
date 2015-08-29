cmake_minimum_required(VERSION 3.3)
project(ntg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    Code/include/AABB.hpp
    Code/include/BB.hpp
    Code/include/collisionGeneration.hpp
    Code/include/Drawable.hpp
    Code/include/Engine.hpp
    Code/include/Module.hpp
    Code/include/MultiplayerObject.hpp
    Code/include/Tank.hpp
    Code/include/Track.hpp
    Code/src/AABB.cpp
    Code/src/Drawable.cpp
    Code/src/MultiplayerObject.cpp
    Code/src/Tank.cpp
    Code/util/lodepng.cpp
    Code/util/lodepng.h
    Code/main.cpp)

add_executable(ntg ${SOURCE_FILES})
target_link_libraries(ntg GL glfw)