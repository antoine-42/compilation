cmake_minimum_required(VERSION 3.13)
project(bugs)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.c)

add_executable(out.o ${SOURCE_FILES})
