cmake_minimum_required(VERSION 3.23)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
    src/Main.cpp
    src/Menu/Menu.cpp
    src/Menu/TimeMenu.cpp
    src/Interface/src/Button.cpp
)

set(HEADERS
    src/Menu/Menu.hpp
    src/Menu/TimeMenu.hpp
    src/Interface/Button.hpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(Chess ${SOURCES})

target_link_libraries(Chess sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
