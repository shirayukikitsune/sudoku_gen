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

#include "digger.h"
#include "solver.h"
#include <algorithm>
#include <random>

sequence::random::random()
: values(81)
{
    std::random_device r;
    std::default_random_engine e(r());

    std::iota(values.begin(), values.end(), 1);
    std::shuffle(values.begin(), values.end(), e);
}

int sequence::random::next_value()
{
    int v = values.back();
    values.pop_back();
    return v;
}

bool sequence::random::has_next()
{
    return !values.empty();
}

int sequence::incremental::next_value()
{
    return current++;
}

bool sequence::incremental::has_next()
{
    return current < 81;
}

void digger::dig(board *b, sequence::sequence* sequence, difficulty::difficulty* difficulty)
{
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(difficulty->min_givens(), difficulty->max_givens());
    int remaining_givens = 81;
    int want_givens = uniform_dist(e);
    solver s;

    while (sequence->has_next()) {
        int i = sequence->next_value();
        int x = i % 9;
        int y = i / 9;
        auto cell = b->get_cell(x, y);
        int row_count = 0, col_count = 0;
        for (int j = 0; j < 9; ++j) {
            if (b->get_cell(x, j)->value > 0) {
                col_count++;
            }
            if (b->get_cell(j, y)->value > 0) {
                row_count++;
            }
        }
        if (col_count <= difficulty->line_lower_bound() || row_count <= difficulty->line_lower_bound()) {
            continue;
        }

        int v = cell->value;
        for (int j = 1; j <= 9; ++j) {
            if (j == v) {
                continue;
            }
            cell->value = 0;
            if (b->is_valid_value(cell->x, cell->y, j)) {
                board board_copy(*b);
                board_copy.get_cell(cell->x, cell->y)->value = j;
                if (s.solve(&board_copy)) {
                    cell->value = v;
                    break;
                }
            }
        }

        if (!cell->value) {
            if (--remaining_givens <= want_givens) {
                break;
            }
        }
    }
}
