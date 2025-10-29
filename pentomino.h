#ifndef PENTOMINO_H
#define PENTOMINO_H

#include <array>

// Stores and calculates information on a specific five-block piece.
class Pentomino {
  public:
    static const int blocks_ = 5;
    // Constructs a Pentomino whose blocks are at the coordinates listed in
    // `shape` and which is represented by the character `letter`. The object
    // does not remember `shape` or its component pointers beyond the scope of
    // the constructor. If `shape` or any of its components are nullptr, throws
    // an exception.
    Pentomino(int shape[blocks_][2], char letter);
    ~Pentomino();
    // Returns an array representing the coordinates of the Pentomino's blocks
    // after the specified transformations are applied. First, flips across the
    // horizontal axis if `h_flip` is true. Then, rotates 90 degrees clockwise
    // `rotation` times.
    std::array<std::array<int, 2>, blocks_> orientShape(bool h_flip,
                                                        int rotation);
    int getHeight();
    int getWidth();
    char getLetter();
    int getRotations();
    bool isSymmetrical();
  protected:
    int shape_[blocks_][2]; // The locacions of the piece's blocks
    int height_; // The height of the piece measured from the centers of blocks
    int width_; // The width of the piece measured from the centers of blocks
    char letter_; // A letter to identify the piece by
    int rotations_; // 4 divided by order of rotational symmetry
    bool symmetrical_; // Whether or not the shape has reflectional symmetry
};

#endif