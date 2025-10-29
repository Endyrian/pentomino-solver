#include "pentomino.h"

#include <array>
#include <stdexcept>
#include <iostream>

Pentomino::Pentomino(int shape[blocks_][2], char letter) : letter_(letter) {
    // Initialize shape
    if (!shape) {
        throw std::invalid_argument("`shape` cannot be nullptr");
    }
    int x_min = INT_MAX;
    height_ = 0;
    int y_min = INT_MAX;
    width_ = 0;
    for (int i = 0; i < blocks_; i++) {
        if (!shape[i])  {
            throw std::invalid_argument(
                "one or more blocks missing from `shape`");
        }
        shape_[i][0] = shape[i][0];
        shape_[i][1] = shape[i][1];

        if (shape[i][0] < x_min) { x_min = shape[i][0]; }
        if (shape[i][0] > height_) { height_ = shape[i][0]; }
        if (shape[i][1] < y_min) { y_min = shape[i][1]; }
        if (shape[i][1] > width_) { width_ = shape[i][1]; }
    }
    for (int i = 0; i < blocks_; i++) {
        shape_[i][0] -= x_min;
        shape_[i][1] -= y_min;
    }
    height_ -= x_min;
    width_ -= y_min;
    
    // Calculate reflectional and rotational symmetry
    bool vertically_symmetric = true;
    bool horizontally_symmetric = true;
    bool pos_diag_symmetric = true;
    bool neg_diag_symmetric = true;
    bool order_2_symmetric = true;
    bool order_4_symmetric = true;
    for (int i = 0; i < blocks_; i++) {
        bool vertically_paired = false;
        bool horizontally_paired = false;
        bool pos_diag_paired = false;
        bool neg_diag_paired = false;
        bool order_2_paired = false;
        bool order_4_paired = false;
        for (int j = 0; j < blocks_; j++) {
            vertically_paired |= (height_ - shape_[i][0] == shape_[j][0] &&
                                  shape_[i][1] == shape_[j][1]);
            horizontally_paired |= (shape_[i][0] == shape_[j][0] &&
                                    width_ - shape_[i][1] == shape_[j][1]);
            pos_diag_paired |= (shape_[i][0] == shape_[j][1] &&
                                shape_[i][1] == shape_[j][0]);
            pos_diag_paired |= (height_ - shape_[i][0] == shape_[j][1] &&
                                shape_[i][1] == height_ - shape_[j][0]);
            order_2_paired |= (height_ - shape_[i][0] == shape_[j][0] &&
                               width_ - shape_[i][1] == shape_[j][1]);
            order_4_paired |= (width_ - shape_[i][1] == shape_[j][0] &&
                               shape_[i][0] == shape_[j][1]);
        }
        vertically_symmetric &= horizontally_paired;
        horizontally_symmetric &= vertically_paired;
        pos_diag_symmetric &= pos_diag_paired;
        neg_diag_symmetric &= neg_diag_paired;
        order_2_symmetric &= order_2_paired;
        order_4_symmetric &= order_4_paired;
    }
    symmetrical_ = vertically_symmetric || horizontally_symmetric ||
                   pos_diag_symmetric || neg_diag_symmetric;
//    if (vertically_symmetric && !horizontally_symmetric) {
//        int temp;
//        for (int i = 0; i < blocks_; i++) {
//            temp = shape_[i][0];
//            shape_[i][0] = shape_[i][1];
//            shape_[i][1] = temp;
//        }
//    }
    if (order_4_symmetric) {
        rotations_ = 1;
    } else if (order_2_symmetric) {
        rotations_ = 2;
    } else {
        rotations_ = 4;
    }
}

Pentomino::~Pentomino() {}

std::array<std::array<int, 2>, Pentomino::blocks_> Pentomino::orientShape(
        bool h_flip, int rotation) {
    std::array<std::array<int, 2>, blocks_> oriented;
    bool v_flip = rotation >= 2;
    bool rotate_90 = rotation % 2 == 1;
    for (int i = 0; i < blocks_; i++) {
        int x = shape_[i][0];
        int y = shape_[i][1];
        if (v_flip != h_flip) {
            x = height_ - x;
        }
        if (v_flip) {
            y = width_ - y;
        }
        if (rotate_90) {
            oriented[i][0] = y;
            oriented[i][1] = height_ - x;
        } else {
            oriented[i][0] = x;
            oriented[i][1] = y;
        }
    }
    return oriented;
}

int Pentomino::getHeight() { return height_; }

int Pentomino::getWidth() { return width_; }

char Pentomino::getLetter() { return letter_; }

int Pentomino::getRotations() { return rotations_; }

bool Pentomino::isSymmetrical() { return symmetrical_; }

// For testing purposes
int main(int argc, char const *argv[]) {
    int shape[5][2];
    for (int i = 0; i < 5; i++) {
        std::cout << "Block " << i << " x: ";
        std::cin >> shape[i][0];
        std::cout << "Block " << i << " y: ";
        std::cin >> shape[i][1];
    }
    char letter;
    std::cout << "Letter representation: ";
    std::cin >> letter;
    Pentomino piece = Pentomino(shape, letter);
    std::cout << "Height: " << piece.getHeight() << std::endl;
    std::cout << "Width: " << piece.getWidth() << std::endl;
    std::cout << "# of unique rotations: " << piece.getRotations()
              << std::endl;
    std::cout << "Reflectional symmetry: " << piece.isSymmetrical()
              << std::endl;
    std::array<std::array<int, 2>, piece.blocks_> orientation;
    orientation = piece.orientShape(!piece.isSymmetrical(),
                                    3 % piece.getRotations());
    std::cout << "Flipped across negative diagonal:\n";
    for (int i = 0; i < piece.blocks_; i++) {
        std::cout << orientation[i][0] << ' ' << orientation[i][1]
                  << std::endl;
    }
    return 0;
}
