cmake_minimum_required(VERSION 3.16)

#project name and version
project(Asteroids VERSION 0.1)

#c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")

add_subdirectory(${CMAKE_SOURCE_DIR}/src)