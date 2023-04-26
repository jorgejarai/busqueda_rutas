cmake_minimum_required(VERSION 3.10)
project(tarea1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tarea1 src/main.cpp src/graph.cpp src/graphreader.cpp
    src/solvers/a-star.cpp src/solvers/dfs.cpp src/solvers/ucs.cpp
    src/solvers/greedy.cpp)

include_directories(include)

add_subdirectory(fmt)
target_link_libraries(tarea1 fmt::fmt)
