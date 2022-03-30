cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tabla VERSION 0.0.1 LANGUAGES CXX)

add_library(tabla INTERFACE)

target_include_directories(tabla INTERFACE include)

include(CTest)
enable_testing()
add_subdirectory(test)
