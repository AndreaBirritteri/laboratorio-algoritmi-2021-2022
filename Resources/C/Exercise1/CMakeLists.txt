cmake_minimum_required(VERSION 3.22)
project(laboratorio_algoritmi_2021_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(..)
include_directories(.)
include_directories(bin)
include_directories(build)
include_directories(files)
include_directories(src)
include_directories(../Unity)

add_executable(laboratorio_algoritmi_2021_2022
        files/piccolo.csv
        src/binaryInsertionSort.c
        src/link.h
        src/main.c
        ../Unity/unity.c
        ../Unity/unity.h
        ../Unity/unity_internals.h)
