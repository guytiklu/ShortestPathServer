cmake_minimum_required(VERSION 3.15)
project(Ex4v2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Ex4v2 main.cpp FileCacheManager.cpp Interfaces.h MySearchable.cpp MySerialServer.cpp MySerialServer.h myTestClientHandler.cpp myTestClientHandler.h serverside.h Solvers.cpp MyClientHandler.cpp MyClientHandler.h)