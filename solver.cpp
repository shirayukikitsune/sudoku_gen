#include "solver.h"

solver::solver()
: e(r())
{
}

bool solver::solve(board* board)
{
    auto c = find_next_available_cell(board);
    if (!c) {
        return true;
    }

    std::vector<int> allowed_vals(9);
    std::iota(allowed_vals.begin(), allowed_vals.end(), 1);
    std::shuffle(allowed_vals.begin(), allowed_vals.end(), e);

    while (!allowed_vals.empty()) {
        int v = allowed_vals.back();
        allowed_vals.pop_back();

        if (!board->is_valid_value(c->x, c->y, v)) {
            continue;
        }

        c->value = v;

        if (board->is_full()) {
            return true;
        }
        if (solve(board)) {
            return true;
        }
    }

    c->value = 0;

    return false;
}

cell* solver::find_next_available_cell(board *board)
{
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            auto c = board->get_cell(x, y);
            if (c->value == 0) {
                return c;
            }
        }
    }

    return nullptr;
}
