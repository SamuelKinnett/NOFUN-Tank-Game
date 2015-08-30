cmake_minimum_required(VERSION 3.3)
project(ntg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        Code/src/AABB.h
        Code/src/BB.h
        Code/src/collisionGeneration.h
        Code/src/Drawable.h
        Code/src/Engine.h
        Code/src/Module.h
        Code/src/MultiplayerObject.h
        Code/src/Tank.h
        Code/src/Track.h
        Code/src/AABB.cpp
        Code/src/Drawable.cpp
        Code/src/MultiplayerObject.cpp
        Code/src/Tank.cpp
        Code/src/util/lodepng.cpp
        Code/src/util/lodepng.h
        Code/client.cpp
        Code/src/DrawableStructure.cpp
        Code/src/DrawableStructure.h)

add_executable(ntg ${SOURCE_FILES})
target_link_libraries(ntg GL glfw)