#include "solver.h"
#include <vector>
#include <iostream>

int main() {

    // Потестим досочки? :)
    std::vector<std::vector<std::vector<unsigned>>> for_testing = {{{1, 2, 3, 4},
                                                                         {5, 6, 7, 8},
                                                                         {9, 10, 11, 12},
                                                                         {13, 14, 15, 0}},

                                                                 {{1, 2, 3, 4},
                                                                         {5, 6, 7, 8},
                                                                         {9, 10, 11, 12},
                                                                         {13, 14, 0,  15}},

                                                                 {{1, 2, 3, 4},
                                                                         {5, 6, 7, 8},
                                                                         {9, 10, 11, 12},
                                                                         {13, 0,  14, 15}},

                                                                 {{1, 2, 3, 4},
                                                                         {5, 6, 7, 8},
                                                                         {9, 10, 11, 12},
                                                                         {0,  13, 14, 15}},

                                                                 {{1, 2, 3, 4},
                                                                         {5, 6, 7, 8},
                                                                         {0, 10, 11, 12},
                                                                         {9,  13, 14, 15}},

                                                                 {{1, 2, 3, 4},
                                                                         {5, 6, 7, 8},
                                                                         {9, 0,  11, 12},
                                                                         {13, 14, 15, 10}}};


    for (const auto &i : for_testing) {
        std::cout << "=====START BOARD===== " << "\n";
        for (const auto &j : i) {
            for (const auto &k : j) {
                std::cout << k << " ";
            }
            std::cout << "\n";
        }

        std::cout << "\n";

        board cur_board(i);
        solver cur_solver(cur_board);

        std::cout << "NEED MOVES = " << cur_solver.moves() << "\n";
        for (const auto &item : cur_solver) {
            std::cout << item.to_string() << "\n";
        }
    }

    board this_board(3);
    solver this_solver(this_board);

    std::cout << "=====RANDOM TEST=====\n";
    std::cout << "=====START BOARD=====\n";

    std::cout << this_board.to_string();

    std::cout << "NEED MOVES = " << this_solver.moves() << "\n";

    for (const auto &item : this_solver) {
        std::cout << item.to_string() << "\n";
    }
}
