cmake_minimum_required(VERSION 3.24)
project(CTest C)

set(CMAKE_C_STANDARD 11)

add_executable(CTest main.c StructureOperation.h DataOperation.h)
