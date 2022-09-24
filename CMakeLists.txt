cmake_minimum_required(VERSION 3.20)
project(PathsnGraphs)

set(CMAKE_CXX_STANDARD 20)

add_executable(PathsnGraphs main.cpp weightedPath.cpp weightedPath.h locationNode.cpp locationNode.h)
