cmake_minimum_required(VERSION 3.16)
project(nQueens)

set(CMAKE_CXX_STANDARD 20)

add_executable(nQueens main.cpp ConsoleInput/GetIntFromConsole.cpp Coordinates/RandomUniqueCoordinateService.cpp Diagonal/Diagonal.cpp FrameBuffer/FrameBuffer.cpp Queen/Queen.cpp Queen/QueenContainer.cpp Board/BoardPrinter.cpp Board/Board.cpp NQueensSolver/NQueensSolver.cpp)
