cmake_minimum_required(VERSION 3.15)
project(gameOfLife C)
set(CMAKE_C_STANDARD 11)

find_package(SDL2 CONFIG REQUIRED)

add_executable(gameOfLife
        main.c
        src/board.c
        src/rules.c
        src/history.c
        src/graphics.c
)

target_link_libraries(gameOfLife PRIVATE SDL2::SDL2 SDL2::SDL2main)
file(COPY resources/grid.txt DESTINATION ${CMAKE_BINARY_DIR}/resources)
