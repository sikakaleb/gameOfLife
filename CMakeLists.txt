cmake_minimum_required(VERSION 3.29)
project(gameOfLife C)

set(CMAKE_C_STANDARD 11)

# Chemin vers SDL2
set(CMAKE_PREFIX_PATH "C:/SDL2")
set(SDL2_DIR "C:/SDL2/cmake")

# Trouver SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(gameOfLife main.c
        src/board.c
        src/board.h
        src/rules.c
        src/rules.h
        src/history.h
        src/history.c
        src/graphics.c
        src/graphics.h)
