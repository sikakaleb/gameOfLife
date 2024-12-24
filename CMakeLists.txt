cmake_minimum_required(VERSION 3.29)
project(gameOfLife C)

set(CMAKE_C_STANDARD 11)

add_executable(gameOfLife main.c
        src/board.c
        src/board.h
        src/rules.c
        src/rules.h
        src/history.h
        src/history.c
        src/graphics.c
        src/graphics.h)
