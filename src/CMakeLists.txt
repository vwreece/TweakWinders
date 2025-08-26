cmake_minimum_required(VERSION 3.16)
project (Tweakplusplus)


set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Tweakplusplus main.cpp)
set(CMAKE_MAKE_PROGRAM "C:/msys64/mingw64/bin/ninja.exe" CACHE FILEPATH "Ninja")
