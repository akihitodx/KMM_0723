cmake_minimum_required(VERSION 3.16)
project(KMM_0723)

set(CMAKE_CXX_STANDARD 17)

add_executable(KMM_0723 main.cpp types.h structure/graph.cpp structure/index.cpp structure/match.cpp alg/alg.cpp structure/result.h structure/result.cpp)
