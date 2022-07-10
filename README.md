# sudoku_gen - a simple Sudoku puzzle generator

Sudoku is a logic puzzle where the player has to solve the puzzle
by finding all missing numbers in the board.

Its rules are fairly simple:

1. Each number can be placed in each row only once
2. Each number can be placed in each column only once
3. Each number can be placed in a 3x3 block only once

Some puzzles may have more than one solution, given the same
starting board.

This application generates boards in several difficulty levels and
all solutions are guaranteed to be unique. 

## License

This application is licensed under the Apache License 2.0.
See file LICENSE for more details.

## Building the application

To build this application, it is required to have installed:

  - C++23 compatible compiler
  - CMake
  - boost 1.71 or higher

After having these requirements met, one can simply use CMake
to generate the build files using these commands:

    mkdir cmake-build-release
    cd cmake-build-release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . --target sudoku_gen -- -j 4

This will create an executable inside the cmake-build-release
directory called `sudoku_gen`. By starting the application, a
generated sudoku puzzle will be printed to STDOUT. 

Example output:

    > sudoku_gen
    0 0 0 0 0 0 0 0 0 
    0 0 0 0 7 0 5 3 4
    0 0 0 8 0 5 0 2 1
    0 0 0 0 0 2 0 0 7
    0 0 0 0 1 0 0 8 0
    0 0 0 5 0 0 6 1 0
    0 1 3 0 0 4 0 0 6
    0 0 0 0 0 1 0 0 8
    0 4 2 0 9 7 0 0 0 

0 means an empty cell and any non-zero digit is a given to solve
the puzzle. 


