#include <functional>
#include <string>
#include <iostream>

#include "IntMatrix.h"

using mtm::IntMatrix;

IntMatrix::IntMatrix(Dimensions dims, int initial) :
        dims(dims.getRow(), dims.getCol()), array(new int[dims.getRow() * dims.getCol()]) {
    for (int i = 0; i < dims.getRow() * dims.getCol(); i++) {
        array[i] = initial;
    }
}

IntMatrix::IntMatrix(const IntMatrix& matrix) :
        dims(matrix.height(), matrix.width()), array(new int[matrix.size()]) {
    (*this) = matrix;
}

IntMatrix::~IntMatrix() {
    delete array;
}


int IntMatrix::height() const {
    return dims.getRow();
}

int IntMatrix::width() const {
    return dims.getCol();
}

int IntMatrix::size() const {
    return height() * width();
}

IntMatrix IntMatrix::Identity(int size) {
    Dimensions dims(size, size);
    IntMatrix i_matrix(dims);
    for (int i = 0; i < size; i++) {
        i_matrix(i, i) = 1;
    }
    return i_matrix;
}

IntMatrix IntMatrix::transpose() const {
    Dimensions transpose_dims(width(), height());
    IntMatrix transpose_matrix(transpose_dims);

    for (int i = 0; i < transpose_matrix.height(); i++) {
        for (int j = 0; j < transpose_matrix.width(); j++) {
            transpose_matrix(i, j) = (*this)(j, i);
        }
    }
    return transpose_matrix;
}

IntMatrix& IntMatrix::operator=(const IntMatrix& matrix) {
    if (this == &matrix) {
        return *this;
    }

    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*this)(i, j) = matrix(i, j);
        }
    }
    return *this;
}

int& IntMatrix::operator()(int row, int col) {
    return array[row * height() + col];
}

int& IntMatrix::operator()(int row, int col) const {
    return array[row * height() + col];
}