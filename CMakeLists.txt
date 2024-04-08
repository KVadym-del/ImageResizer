cmake_minimum_required(VERSION 3.28)
project(ImageResizer C)

find_package(Stb REQUIRED)
set(CMAKE_C_STANDARD 23)

add_executable(ImageResizer main.c)
target_include_directories(ImageResizer PRIVATE ${Stb_INCLUDE_DIR})
