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
                for (int r = 0; r < rotations; r++) {
                    if (canPlacePentomino(grid, piece, x, y, false, r)) {
                        std::array<std::array<char, 8>, 8> p_grid;
                        p_grid = placePentomino(grid, piece, x, y, false, r);
                        new_grids.push_back(p_grid);
                        if (!symmetrical) {
                            std::array<std::array<char, 8>, 8> f_grid;
                            f_grid = placePentomino(grid, piece, x, y, true,
                                                    r);
                            new_grids.push_back(f_grid);
                        }
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

    int u_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 2}};
    solutions = addPentomino(solutions, Pentomino(u_shape, 'u'));
    int n_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {3, 1}};
    solutions = addPentomino(solutions, Pentomino(n_shape, 'n'));
    int v_shape[5][2] = {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {0, 2}};
    solutions = addPentomino(solutions, Pentomino(v_shape, 'v'));
    int x_shape[5][2] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}, {1, 2}};
    solutions = addPentomino(solutions, Pentomino(x_shape, 'x'));
    int i_shape[5][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
    solutions = addPentomino(solutions, Pentomino(i_shape, 'i'));
    int y_shape[5][2] = {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {0, 3}};
    solutions = addPentomino(solutions, Pentomino(y_shape, 'y'));
    int t_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2, 0}};
    solutions = addPentomino(solutions, Pentomino(t_shape, 't'));
    int p_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {2, 0}};
    solutions = addPentomino(solutions, Pentomino(p_shape, 'p'));
    int w_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}};
    solutions = addPentomino(solutions, Pentomino(w_shape, 'w'));
    int l_shape[5][2] = {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {0, 3}};
    solutions = addPentomino(solutions, Pentomino(l_shape, 'l'));
    int f_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {1, 2}};
    solutions = addPentomino(solutions, Pentomino(f_shape, 'f'));
    int z_shape[5][2] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}, {2, 2}};
    solutions = addPentomino(solutions, Pentomino(z_shape, 'z'));

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
