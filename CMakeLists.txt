cmake_minimum_required(VERSION 3.3)
project(ntg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    Code/src/AABB.hpp
    Code/src/BB.hpp
    Code/src/collisionGeneration.hpp
    Code/src/Drawable.hpp
    Code/src/Engine.hpp
    Code/src/Module.hpp
    Code/src/MultiplayerObject.hpp
    Code/src/Tank.hpp
    Code/src/Track.hpp
    Code/src/AABB.cpp
    Code/src/Drawable.cpp
    Code/src/MultiplayerObject.cpp
    Code/src/Tank.cpp
        Code/src/util/lodepng.cpp
        Code/src/util/lodepng.h
        Code/client.cpp)

add_executable(ntg ${SOURCE_FILES})
target_link_libraries(ntg GL glfw)