cmake_minimum_required(VERSION 3.28)
project(DjikstraGPS C)

set(CMAKE_C_STANDARD 11)

add_executable(DjikstraGPS src/main.c
        include/list.h)

add_executable(test src/test.c
        src/list.c
        src/util.c
        src/dyntable.c
        src/tree.c
)