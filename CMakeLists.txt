project("NOFUN Tank Game")

add_executable(NTG 	Code/main.cpp
					Code/src/tank.cpp
					Code/include/tank.h
					Code/src/AABB.cpp
					Code/include/AABB.h)

SET (CMAKE_CXX_FLAGS "-std=c++0x")