cmake_minimum_required(VERSION 3.2)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
    main.cpp
)

# set(HEADERS
# )

add_executable(Chess ${SOURCES})

target_link_libraries(Chess sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
