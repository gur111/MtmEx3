#include <functional>
#include <string>
#include <iostream>

#include "IntMatrix.h"

void mtm::IntMatrix::assignment(const IntMatrix& matrix) {
    for (int i = 0; i < height(); i++) {
        array[i] = new int[width()];
        for (int j = 0; j <width(); j++) {
            array[i][j] = matrix[i][j];//todo: needs to be changed to () operator
        }
    }
}
mtm::IntMatrix::IntMatrix(Dimensions dims, int initial) :
        dims(dims.getRow(), dims.getCol()), array(new int*[dims.getRow()]) {
    for (int i = 0; i < dims.getRow(); i++) {
        array[i] = new int[dims.getCol()];
        for (int j = 0; j < dims.getCol(); j++) {
            array[i][j] = initial;
        }
    }
}

mtm::IntMatrix::IntMatrix(const IntMatrix& matrix) :
        dims(matrix.height(), matrix.width()), array(new int*[height()]) {
    assignment(matrix);
}

mtm::IntMatrix::~IntMatrix() {
    deleteArray();
}

void mtm::IntMatrix::deleteArray() {
    for (int i = 0; i < height(); i++) {
        delete[] array[i];
    }
    delete (array);
}

int mtm::IntMatrix::height() const {
    return dims.getRow();
}

int mtm::IntMatrix::width() const {
    return dims.getCol();
}

int mtm::IntMatrix::size() const {
    return height() * width();
}

mtm::IntMatrix& mtm::IntMatrix::Identity(int size) {
    Dimensions dims(size, size);
    IntMatrix* i_matrix = new IntMatrix(dims, 1);
    return *i_matrix;
}

mtm::IntMatrix& mtm::IntMatrix::transpose() const {
    Dimensions transpose_dims(height(), width());
    IntMatrix* transpose_matrix = new IntMatrix(transpose_dims);
    for (int i = 0; i < transpose_matrix->height(); i++) {
        for (int j = 0; j < transpose_matrix->width(); j++) {
            transpose_matrix[i][j] = this[j][i];//todo: needs to be changed to () operator
        }
    }
    return *transpose_matrix ;
}

mtm::IntMatrix& mtm::IntMatrix::operator=(const IntMatrix& matrix) {
    if (this == &matrix) {
        return *this;
    }
    deleteArray();
    dims = matrix.dims;
    assignment(matrix);
    return *this;
}
