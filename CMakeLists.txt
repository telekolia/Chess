cmake_minimum_required(VERSION 3.2)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
    src/Main.cpp
    src/Menu/Menu.cpp
    src/Interface/src/Button.cpp
    src/Chessboard/Chessboard.cpp
    src/Chessboard/Board/Board.cpp
    src/Chessboard/Piece/Piece.cpp
    src/Chessboard/ChessEngine/ChessEngine.cpp
)

set(HEADERS
    src/Menu/Menu.hpp
    src/Interface/Button.hpp
    src/Chessboard/Chessboard.hpp
    src/Chessboard/Board/Board.hpp
    src/Chessboard/Piece/Piece.hpp
    src/Chessboard/ChessEngine/ChessEngine.hpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(Chess ${SOURCES})

target_link_libraries(Chess sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
