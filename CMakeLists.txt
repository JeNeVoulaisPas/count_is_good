cmake_minimum_required(VERSION 3.10)

project(count_is_good VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(MyLibrary
        src/MT.cpp
        src/TileSet.cpp
        src/Solver.cpp
        src/main.cpp
)


target_include_directories(MyLibrary PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(count_is_good
        src/main.cpp

)

target_link_libraries(count_is_good PRIVATE MyLibrary)
