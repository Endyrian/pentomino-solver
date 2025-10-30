#include "pentomino.h"

#include <array>
#include <vector>
#include <iostream>

std::vector<std::array<std::array<char, 8>, 8>> addPentomino(
        std::vector<std::array<std::array<char, 8>, 8>> grids,
        Pentomino piece) {
    std::vector<std::array<std::array<char, 8>, 8>> added_grids;
    // TODO: test all possible placements for the piece
    return added_grids;
}

int main(int argc, char const *argv[]) {
    std::vector<std::array<std::array<char, 8>, 8>> solutions;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y <= x; y++) {
            std::array<std::array<char, 8>, 8> grid;
            for (int i = 0; i < 8; i++) {
                grid[i] = {'0', '0', '0', '0', '0', '0', '0', '0'};
            }
            grid[x][y] = '4';
            grid[x+1][y] = '4';
            grid[x+1][y+1] = '4';
            grid[x][y+1] = '4';
            solutions.push_back(grid);
        }
    }
    
    // TODO: test all pentomino placements

    for (auto &&solved : solutions) {
        std::cout << "-----" << std::endl;
        for (auto &&x : solved) {
            for (auto &&y : x) {
                std::cout << y << ' ';
            }
            std::cout << std::endl;
        }
    }
    std::cout << "-----" << std::endl;
    return 0;
}
