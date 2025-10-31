#include "pentomino.h"

#include <array>
#include <vector>
#include <iostream>

// Returns whether `piece` can fit in `grid` at the specified location after
//  undergoing thespecified transformations.
bool canPlacePentomino(std::array<std::array<char, 8>, 8> grid,
                       Pentomino piece, int x, int y, bool flip,
                       int rotation) {
    int height = piece.getHeight();
    int width = piece.getWidth();
    if (rotation % 2 == 0) {
        if (x + height >= 8 && y || width >= 8) {
            return false;
        }
    } else if (y + height >= 8 && x + width >= 8) {
        return false;
    }
    std::array<std::array<int, 2>, piece.blocks_> coords = piece.orientShape(
            flip, rotation);
    for (auto &&block : coords) {
        if (grid[x + block[0]][y + block[1]] != '0') {
            return false;
        }
    }
    return true;
}

// Returns a version of `grid` with `piece` added at the specified location
// after undergoing the specified transformations.
std::array<std::array<char, 8>, 8> placePentomino(
        std::array<std::array<char, 8>, 8> grid, Pentomino piece,
        int x, int y, bool flip, int rotation) {
    std::array<std::array<char, 8>, 8> new_grid = grid;
    std::array<std::array<int, 2>, piece.blocks_> coords = piece.orientShape(
            flip, rotation);
    for (auto &&block : coords) {
        new_grid[x + block[0]][y + block[1]] = piece.getLetter();
    }
    return new_grid;
}

// Returns a vector of all possible puzzle grid arrangements which can be
// obtained by adding `piece` in a valid location to one of the grids in
// `old_grids`
std::vector<std::array<std::array<char, 8>, 8>> addPentomino(
        std::vector<std::array<std::array<char, 8>, 8>> old_grids,
        Pentomino piece) {
    std::vector<std::array<std::array<char, 8>, 8>> new_grids;
    int rotations = piece.getRotations();
    bool symmetrical = piece.isSymmetrical();
    for (auto &&grid : old_grids) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                for (int i = 0; i < rotations; i++) {
                    if (canPlacePentomino(grid, piece, x, y, false, i)) {
                        std::array<std::array<char, 8>, 8> p_grid;
                        p_grid = placePentomino(grid, piece, x, y, false, i);
                        // TODO: test all possible placements for the piece
                    }
                    
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
