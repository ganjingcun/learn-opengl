cmake_minimum_required(VERSION 3.3)
project(learm_opengl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_SUBDIRECTORY(src bin)
