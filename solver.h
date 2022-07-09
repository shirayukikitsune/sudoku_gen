#pragma once

#include "board.h"
#include <random>

class solver {
public:
    solver();
    bool solve(board* board);

private:
    static cell* find_next_available_cell(board* board);

    std::random_device r;
    std::mt19937 e;
};
