cmake_minimum_required(VERSION 3.20)
project(sudoku_gen)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost 1.71.0 REQUIRED log program_options)

add_executable(sudoku_gen main.cpp board.cpp board.h cell.h board_generator.cpp board_generator.h solver.cpp solver.h digger.cpp digger.h)
target_link_libraries(sudoku_gen PUBLIC Boost::boost Boost::log Boost::program_options)
