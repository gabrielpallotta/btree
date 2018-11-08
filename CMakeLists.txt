cmake_minimum_required(VERSION 3.9.2)
project(btree)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(btree ${SOURCE_FILES} main.cpp) 