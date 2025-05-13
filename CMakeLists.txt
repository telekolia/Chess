cmake_minimum_required(VERSION 3.28)
set(project "Chess")
project("${project}" LANGUAGES CXX)

set(${project}_SOURCES
        src/main.cpp)

# set(${project}_HEADERS
#         fraction.hpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

if(ENABLE_DEBUG)
    target_compile_options(${project} PRIVATE -g)
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${project}
        ${${project}_SOURCE_LIST})
target_compile_features(${project} PRIVATE cxx_std_17)
target_link_libraries(${project} PRIVATE SFML::Graphics)
