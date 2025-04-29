#include <catch2/catch_test_macros.hpp>

#include "src/sudoku/board.h"

std::array<int, 81> knownSolved = {
        8, 7, 5, 4, 9, 2, 3, 1, 6,
        2, 4, 1, 6, 7, 3, 5, 8, 9,
        9, 6, 3, 1, 8, 5, 2, 7, 4,
        6, 9, 7, 2, 1, 8, 4, 5, 3,
        5, 3, 8, 7, 4, 6, 1, 9, 2,
        1, 2, 4, 5, 3, 9, 7, 6, 8,
        4, 5, 2, 9, 6, 7, 8, 3, 1,
        3, 1, 6, 8, 5, 4, 9, 2, 7,
        7, 8, 9, 3, 2, 1, 6, 4, 5,
};
std::string expected_zero = "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0";
std::string expected_known = "8 7 5 4 9 2 3 1 6\n"
                             "2 4 1 6 7 3 5 8 9\n"
                             "9 6 3 1 8 5 2 7 4\n"
                             "6 9 7 2 1 8 4 5 3\n"
                             "5 3 8 7 4 6 1 9 2\n"
                             "1 2 4 5 3 9 7 6 8\n"
                             "4 5 2 9 6 7 8 3 1\n"
                             "3 1 6 8 5 4 9 2 7\n"
                             "7 8 9 3 2 1 6 4 5";

SCENARIO("sudoku boards", "[board]") {
    GIVEN("an empty board") {
        board board;

        REQUIRE_FALSE(board.is_full());
        REQUIRE_FALSE(board.validate());

        THEN("all cells must be zero") {
            for (int x = 0; x < 9; ++x) {
                for (int y = 0; y < 9; ++y) {
                    REQUIRE(board.get_cell(x, y)->value == 0);
                }
            }

            auto str = board.to_string();
            REQUIRE(str == expected_zero);
        }
    }

    GIVEN("a solved board") {
        board board(knownSolved);

        REQUIRE(board.is_full());
        REQUIRE(board.validate());
        auto str = board.to_string();
        REQUIRE(str == expected_known);

        WHEN("modifying a cell") {
            board.get_cell(0, 0)->value = 3;

            THEN("should not be valid") {
                REQUIRE_FALSE(board.validate());
            }
        }
    }
}
