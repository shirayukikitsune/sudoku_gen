/*
   Copyright 2022 Bruno Rodrigues Ferreira

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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
