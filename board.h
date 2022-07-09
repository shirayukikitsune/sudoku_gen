#pragma once

#include "cell.h"
#include <set>

class board {
public:
    board();

    cell* get_cell(int x, int y);

    bool is_full();

    bool validate();
    bool is_valid_value(int x, int y, int value);

    void print();

private:
    cell cells[9][9];

    bool is_valid_column_value(int x, int y, int value);
    bool is_valid_row_value(int x, int y, int value);
    bool is_valid_block_value(int x, int y, int value);
};
