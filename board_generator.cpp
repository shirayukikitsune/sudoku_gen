#include "board_generator.h"

#include <algorithm>
#include <vector>

board_generator::board_generator()
: e(r())
{
}

void board_generator::generate(board* board)
{
    std::uniform_int_distribution<int> uniform_dist(1, 9);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cell* c;
        do {
            x = uniform_dist(e);
            y = uniform_dist(e);
            c = board->get_cell(x, y);
        } while (c->value != 0);

        std::vector<int> allowed_vals(9);
        std::iota(allowed_vals.begin(), allowed_vals.end(), 1);
        std::shuffle(allowed_vals.begin(), allowed_vals.end(), e);
        int v;

        while (!allowed_vals.empty()) {
            v = allowed_vals.back();
            allowed_vals.pop_back();
            if (board->is_valid_value(x, y, v)) {
                break;
            }
            v = -1;
        }
        if (v == -1) {
            i--;
        } else {
            c->value = v;
        }
    }
}
