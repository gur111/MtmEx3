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

IntMatrix IntMatrix::transpose() const {
    Dimensions transpose_dims(height(), width());
    IntMatrix* transpose_matrix = new IntMatrix(transpose_dims);
    for (int i = 0; i < transpose_matrix->height(); i++) {
        for (int j = 0; j < transpose_matrix->width(); j++) {
            (*transpose_matrix)(i, j) =
                (*this)(j, i);  // todo: needs to be changed to () operator
        }
    }
    return *transpose_matrix;
}

IntMatrix IntMatrix::operator-(const IntMatrix& matrix) const {
    IntMatrix* result_matrix = new IntMatrix(dims);
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*result_matrix)(i, j) = (*this)(i, j) - matrix(i, j);
        }
    }

    return *result_matrix;
}

IntMatrix IntMatrix::operator-() const {
    IntMatrix* result_matrix = new IntMatrix(dims);
    *result_matrix -= *this;

    return *result_matrix;
}

IntMatrix& IntMatrix::operator-=(const IntMatrix& matrix) {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*this)(i, j) -= matrix(i, j);
        }
    }

    return *this;
}

int& IntMatrix::operator()(int row, int col) { return array[row][col]; }

int& IntMatrix::operator()(int row, int col) const { return array[row][col]; }

IntMatrix& IntMatrix::operator=(const IntMatrix& matrix) {
    if (this == &matrix) {
        return *this;
    }

    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            array[i][j] = matrix(i, j);
        }
    }

    return *this;
}

ostream& operator<<(ostream& os, const IntMatrix& matrix) {
    int* flattened = new int[matrix.size()];
    int i = 0;
    for (int curr : matrix) {
        flattened[i++] = curr;
    }

    mtm::printMatrix(flattened,
                     mtm::Dimensions(matrix.height(), matrix.width()));

    return os;
}

IntMatrix::Iterator::Iterator(const IntMatrix* matrix, int index)
    : matrix(matrix), index(index) {}

const int& IntMatrix::Iterator::operator*() const {
    assert(index >= 0 and index < matrix->size());
    return matrix->array[index / matrix->height()][index % matrix->width()];
}

IntMatrix::Iterator& IntMatrix::Iterator::operator++() {
    ++index;
    return *this;
}

IntMatrix::Iterator IntMatrix::Iterator::operator++(int) {
    Iterator result = *this;
    ++*this;
    return result;
}

bool IntMatrix::Iterator::operator==(const Iterator& another) const {
    assert(matrix == another.matrix);
    return index == another.index;
}

bool IntMatrix::Iterator::operator!=(const Iterator& another) const {
    return not(*this == another);
}

IntMatrix::Iterator IntMatrix::begin() const { return Iterator(this, 0); }

IntMatrix::Iterator IntMatrix::end() const { return Iterator(this, size()); }
