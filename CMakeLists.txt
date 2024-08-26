cmake_minimum_required(VERSION 3.20)
project(Cache)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cache main.cpp Cache.h FullyA.cpp FullyA.h hexConverter.cpp hexConverter.h Direct.cpp Direct.h Sets.cpp Sets.h)
