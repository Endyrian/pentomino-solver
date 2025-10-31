#include "pentomino.h"

#include <array>
#include <vector>
#include <iostream>

// Returns a vector of all possible puzzle grid arrangements which can be
// obtained by adding `piece` in a valid location to one of the grids in
// `old_grids`
std::vector<std::array<std::array<char, 8>, 8>> addPentomino(
        std::vector<std::array<std::array<char, 8>, 8>> old_grids,
        Pentomino piece) {
    std::vector<std::array<std::array<char, 8>, 8>> new_grids;
    int rotations = piece.getRotations();
    bool symmetrical = piece.isSymmetrical();
    int height = piece.getHeight();
    int width = piece.getWidth();
    for (auto &&grid : old_grids) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                for (int i = 0; i < rotations; i++) {
                    if (i % 2 == 0 && x + height < 8 && y + width < 8) {
                        /* code */
                    } else if (y + height < 8 && x + width < 8) {
                        /* code */
                    }
                    
                    // TODO: test all possible placements for the piece
                }
                
            }
            
        }

    }
    
    return new_grids;
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
