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

#include "board.h"
#include <sstream>

board::board()
{
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            cells[x][y].x = x;
            cells[x][y].y = y;
        }
    }
}

cell* board::get_cell(int x, int y)
{
    return &cells[x][y];
}

bool board::is_full()
{
    for (auto & row : cells) {
        for (auto & cell : row) {
            if (cell.value == 0) {
                return false;
            }
        }
    }

    return true;
}

bool board::validate()
{
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            if (!is_valid_value(x, y, cells[x][y].value)) {
                return false;
            }
        }
    }
    return true;
}

bool board::is_valid_value(int x, int y, int value)
{
    return is_valid_row_value(x, y, value) && is_valid_column_value(x, y, value) && is_valid_block_value(x, y, value);
}

bool board::is_valid_column_value(int x, int y, int value)
{
    for (int dy = 0; dy < 9; ++dy) {
        if (dy == y) {
            continue;
        }
        if (cells[x][dy].value == value) {
            return false;
        }
    }

    return true;
}

bool board::is_valid_row_value(int x, int y, int value)
{
    for (int dx = 0; dx < 9; ++dx) {
        if (dx == x) {
            continue;
        }
        if (cells[dx][y].value == value) {
            return false;
        }
    }

    return true;
}

bool board::is_valid_block_value(int x, int y, int value)
{
    int x0 = (x / 3) * 3;
    int x1 = x0 + 3;
    int y0 = (y / 3) * 3;
    int y1 = y0 + 3;

    for (int dx = x0; dx < x1; ++dx) {
        for (int dy = y0; dy < y1; ++dy) {
            if (dx == x && dy == y) {
                continue;
            }

            if (cells[dx][dy].value == value) {
                return false;
            }
        }
    }

    return true;
}

std::string board::to_string()
{
    std::stringstream ss;
    for (auto & row : cells) {
        for (auto & cell : row) {
            ss << cell.value << " ";
        }
        ss << "\n";
    }
    return ss.str();
}
