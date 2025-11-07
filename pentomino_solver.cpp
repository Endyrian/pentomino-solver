#include "pentomino.h"

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

int square_positions_checked = 0;

// Returns whether `piece` can fit in `grid` at the specified location after
// undergoing thespecified transformations.
// DEPRECATED: Merged into `tryPentomino()`.
bool canPlacePentomino(std::array<std::array<char, 8>, 8> grid,
                       Pentomino piece, int x, int y, bool flip,
                       int rotation) {
    int height = piece.getHeight();
    int width = piece.getWidth();
    if (rotation % 2 == 0) {
        if (x + height >= 8 || y + width >= 8) {
            return false;
        }
    } else if (y + height >= 8 || x + width >= 8) {
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
// DEPRECATED: Merged into `tryPentomino()`.
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
// `old_grids`.
// DEPRECATED: uses too much memory.
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

// If the specified placement of the piece at index `piece_number` in `pieces`
// in `base_grid` is valid, returns the result of running `solveGrid()` on that
// placement. Otherwise, returns an empty vector.
std::vector<std::array<std::array<char, 8>, 8>> tryPentomino(
        std::array<std::array<char, 8>, 8> base_grid,
        std::vector<Pentomino> pieces, int piece_number,
        int x, int y, bool flip, int rotation,
        int unique_rotations = 4, bool reflect_unique = true) {
    std::vector<std::array<std::array<char, 8>, 8>> no_solutions;

    // Check if inbounds
    int height = pieces[piece_number].getHeight();
    int width = pieces[piece_number].getWidth();
    if (rotation % 2 == 0) {
        if (x + height >= 8 || y + width >= 8) {
            return no_solutions;
        }
    } else if (y + height >= 8 || x + width >= 8) {
        return no_solutions;
    }

    // Check if non-overlapping
    std::array<std::array<char, 8>, 8> new_grid = base_grid;
    std::array<std::array<int, 2>, Pentomino::blocks_> coords =
            pieces[piece_number].orientShape(flip, rotation);
    for (auto &&block : coords) {
        if (base_grid[x + block[0]][y + block[1]] != '0') {
            return no_solutions;
        }
        new_grid[x + block[0]][y + block[1]] = pieces[piece_number].getLetter();
    }
    
    // Pass through to next layer of solveGrid
    return solveGrid(new_grid, pieces, piece_number + 1, unique_rotations,
                     reflect_unique);
}

// Returns a vector of all possible solutions containing all the pieces
// specified in `pieces`, where all pieces numbered less that `piece_number`
// are in the same locations as they are in `base_grid`. `unique_rotations`
// indicates how many ways the piece can be rotated without resulting in
// duplicate grids. `reflect_unique` indicates whether flipping the piece
// will result in functionally distinct grids.
std::vector<std::array<std::array<char, 8>, 8>> solveGrid(
        std::array<std::array<char, 8>, 8> base_grid,
        std::vector<Pentomino> pieces, int piece_number,
        int unique_rotations = 4, bool reflect_unique = true) {
    std::vector<std::array<std::array<char, 8>, 8>> solutions;

    // base case
    if (piece_number == pieces.size()) {
        solutions.push_back(base_grid);
        return solutions;
    }
    
    // recursive case
    int rotations = pieces[piece_number].getRotations();
    bool asymmetrical = !pieces[piece_number].isSymmetrical();
    int next_unique_rotations = std::max(unique_rotations, rotations);
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (piece_number == 0) {
                std::cout << square_positions_checked // print progress
                        << (x / 8.0 + y / 64.0) * 10 << '%' << std::endl;
            }

            for (int r = 0; r < rotations && r < unique_rotations; r++) {
                std::vector<std::array<std::array<char, 8>, 8>>
                sub_solutions = tryPentomino(base_grid, pieces,
                                             piece_number + 1, x, y, false, r,
                                             next_unique_rotations,
                                             reflect_unique || asymmetrical);
                solutions.insert(solutions.end(), sub_solutions.begin(),
                                 sub_solutions.end());
                
                if (asymmetrical && reflect_unique) {
                    std::vector<std::array<std::array<char, 8>, 8>>
                    sub_solutions = tryPentomino(base_grid, pieces,
                                                 piece_number + 1, x, y, false,
                                                 r, next_unique_rotations);
                    solutions.insert(solutions.end(),
                                     sub_solutions.begin(),
                                     sub_solutions.end());
                }
            }
        }
    }
    return solutions;
}

int main(int argc, char const *argv[]) {
    std::vector<Pentomino> pieces;
    int x_shape[5][2] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}, {1, 2}};
    pieces.push_back(Pentomino(x_shape, 'x'));
    int i_shape[5][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
    pieces.push_back(Pentomino(i_shape, 'i'));
    int z_shape[5][2] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}, {2, 2}};
    pieces.push_back(Pentomino(z_shape, 'z'));
    int t_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2, 0}};
    pieces.push_back(Pentomino(t_shape, 't'));
    int v_shape[5][2] = {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {0, 2}};
    pieces.push_back(Pentomino(v_shape, 'v'));
    int w_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}};
    pieces.push_back(Pentomino(w_shape, 'w'));
    int u_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 2}};
    pieces.push_back(Pentomino(u_shape, 'u'));
    int l_shape[5][2] = {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {0, 3}};
    pieces.push_back(Pentomino(l_shape, 'l'));
    int n_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {3, 1}};
    pieces.push_back(Pentomino(n_shape, 'n'));
    int y_shape[5][2] = {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {0, 3}};
    pieces.push_back(Pentomino(y_shape, 'y'));
    int f_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {1, 2}};
    pieces.push_back(Pentomino(f_shape, 'f'));
    int p_shape[5][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {2, 0}};
    pieces.push_back(Pentomino(p_shape, 'p'));
    std::cout << "Pentominoes initialized, starting search." << std::endl;

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
            std::vector<std::array<std::array<char, 8>, 8>> sub_solutions;
            sub_solutions = solveGrid(grid, pieces, 0, (y == 3) ? 1 : 4,
                                      x != 3 && y != x);
            solutions.insert(solutions.end(), sub_solutions.begin(),
                             sub_solutions.end());
            square_positions_checked++;
        }
    }
    std::cout << "100%" << std::endl << "Search complete." << std::endl;

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
