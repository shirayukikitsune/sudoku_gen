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

#pragma once

#include "cell.h"
#include <set>
#include <string>

class board {
public:
    board();

    cell* get_cell(int x, int y);

    bool is_full();

    bool validate();
    bool is_valid_value(int x, int y, int value);

    std::string to_string();

private:
    cell cells[9][9];

    bool is_valid_column_value(int x, int y, int value);
    bool is_valid_row_value(int x, int y, int value);
    bool is_valid_block_value(int x, int y, int value);
};
