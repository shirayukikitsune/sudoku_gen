#pragma once

#include "board.h"
#include <random>

class board_generator {
public:
    board_generator();
    void generate(board* board);

private:
    std::random_device r;
    std::mt19937 e;

    static constexpr int n = 11;
};
