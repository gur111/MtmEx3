#include "IntMatrix.h"

#include <assert.h>

#include <functional>
#include <iostream>
#include <string>

using mtm::IntMatrix;

namespace mtm {

IntMatrix::IntMatrix(Dimensions dims, int initial)
    : dims(dims.getRow(), dims.getCol()),
      array(new int[dims.getRow() * dims.getCol()]) {
    for (int i = 0; i < dims.getRow() * dims.getCol(); i++) {
        array[i] = initial;
    }
}

IntMatrix::IntMatrix(const IntMatrix& matrix)
    : dims(matrix.height(), matrix.width()), array(new int[matrix.size()]) {
    (*this) = matrix;
}

IntMatrix::~IntMatrix() { delete array; }

int IntMatrix::height() const { return dims.getRow(); }

int IntMatrix::width() const { return dims.getCol(); }

int IntMatrix::size() const { return height() * width(); }

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

IntMatrix IntMatrix::operator-(const IntMatrix& matrix) const {
    IntMatrix result_matrix(dims);
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            result_matrix(i, j) = (*this)(i, j) - matrix(i, j);
        }
    }

    return result_matrix;
}

IntMatrix IntMatrix::operator-() const {
    IntMatrix result_matrix(dims);
    result_matrix -= *this;

    return result_matrix;
}

// TODO: Consider merging w/ operator-(matrix) somehow
IntMatrix IntMatrix::operator+(const IntMatrix& matrix) const {
    IntMatrix result_matrix(dims);
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            result_matrix(i, j) = (*this)(i, j) + matrix(i, j);
        }
    }
    return result_matrix;
}

IntMatrix IntMatrix::operator+(int scalar) const {
    IntMatrix result_matrix(*this);
    // It's better to use += as it won't create yet another matrix
    return result_matrix += scalar;
}

IntMatrix operator+(int scalar, const IntMatrix& matrix_b) {
    return matrix_b + scalar;
}

IntMatrix& IntMatrix::operator-=(const IntMatrix& matrix) {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*this)(i, j) -= matrix(i, j);
        }
    }

    return *this;
}

IntMatrix& IntMatrix::operator+=(int scalar) {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*this)(i, j) += scalar;
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

IntMatrix& IntMatrix::operator=(const IntMatrix& matrix) {
    if (this == &matrix) {
        return *this;
    }
    iterator it_this = this->begin();

    for (const_iterator it_other = matrix.begin(); it_other != matrix.end();
         it_other++, it_this++) {
        *it_this = *it_other;
    }

    return *this;
}

IntMatrix IntMatrix::operator>(int num) const {
    IntMatrix result(*this);
    iterator it_result = result.begin();

    for (const_iterator it_this = this->begin(); it_this != this->end();
         it_this++, it_result++) {
        *it_result = *it_this > num ? 1 : 0;
    }

    return result;
}
IntMatrix IntMatrix::operator<(int num) const {
    IntMatrix result(*this);
    iterator it_result = result.begin();

    for (const_iterator it_this = this->begin(); it_this != this->end();
         it_this++, it_result++) {
        *it_result = *it_this < num ? 1 : 0;
    }

    return result;
}

IntMatrix IntMatrix::operator>=(int num) const {
    IntMatrix ones(dims, 1);
    IntMatrix result = ones - (*this < num);
    return result;
}

IntMatrix IntMatrix::operator<=(int num) const {
    IntMatrix ones(dims, 1);
    IntMatrix result = ones - (*this > num);
    return result;
}

IntMatrix IntMatrix::operator!=(int num) const {
    IntMatrix ones(dims, 1);
    IntMatrix result = ones - (*this == num);
    return result;
}

IntMatrix IntMatrix::operator==(int num) const {
    IntMatrix result(*this);
    iterator it_result = result.begin();

    for (const_iterator it_this = this->begin(); it_this != this->end();
         it_this++, it_result++) {
        *it_result = *it_this == num ? 1 : 0;
    }

    return result;
}

IntMatrix IntMatrix::operator==(const IntMatrix& matrix) const {
    IntMatrix result(*this);
    iterator it_result = result.begin();

    for (const_iterator it_other = matrix.begin(), it_this = this->begin();
         it_this != this->end(); it_this++, it_result++, it_other++) {
        *it_result = *it_this == *it_other ? 1 : 0;
    }

    return result;
}

bool any(const IntMatrix& matrix) {
    for (IntMatrix::const_iterator it = matrix.begin(); it != matrix.end();
         it++) {
        if (*it != 0) {
            return true;
        }
    }

    return false;
}

bool all(const IntMatrix& matrix) {
    for (IntMatrix::const_iterator it = matrix.begin(); it != matrix.end();
         it++) {
        if (*it == 0) {
            return false;
        }
    }

    return true;
}

const int& IntMatrix::const_iterator::operator*() const {
    assert(index >= 0 and index < this->matrix->size());
    return this->matrix->array[index];
}

IntMatrix::iterator::iterator(IntMatrix* matrix, int index)
    : matrix(matrix), index(index) {}

int& IntMatrix::iterator::operator*() const {
    assert(index >= 0 and index < matrix->size());
    return matrix->array[index];
}

IntMatrix::iterator& IntMatrix::iterator::operator++() {
    ++index;
    return *this;
}

IntMatrix::iterator IntMatrix::iterator::operator++(int) {
    iterator result = *this;
    ++*this;
    return result;
}

bool IntMatrix::iterator::operator==(const iterator& another) const {
    assert(matrix == another.matrix);
    return index == another.index;
}

bool IntMatrix::iterator::operator!=(const iterator& another) const {
    return not(*this == another);
}

IntMatrix::iterator IntMatrix::begin() { return iterator(this, 0); }
IntMatrix::iterator IntMatrix::end() { return iterator(this, size()); }

IntMatrix::const_iterator IntMatrix::begin() const {
    return const_iterator(this, 0);
}
IntMatrix::const_iterator IntMatrix::end() const {
    return const_iterator(this, size());
}

std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix) {
    os << printMatrix(matrix.array,
                      Dimensions(matrix.height(), matrix.width()));

    return os;
}
};  // namespace mtm