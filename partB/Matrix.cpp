#include "Matrix.h"

#include <assert.h>

#include <functional>
#include <iostream>
#include <string>

using mtm::Matrix;

template<class T>
Matrix<T>::Matrix(Dimensions dims, T initial)
        : dims(dims.getRow(), dims.getCol()),
          array(new T[dims.getRow() * dims.getCol()]) {
    if (dims.getCol() <= 0 || dims.getRow() <= 0) {
        throw Matrix<T>::IllegalInitialization();//todo:should i delete the array or dose the stack unwinding doing this for me?
    }
    for (int i = 0; i < dims.getRow() * dims.getCol(); i++) {
        array[i] = initial;
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix& matrix)
        : dims(matrix.height(), matrix.width()), array(new T[matrix.size()]) {
    (*this) = matrix;
}

template<class T>
Matrix<T>::~Matrix() { delete array; }

template<class T>
int Matrix<T>::height() const { return dims.getRow(); }

template<class T>
int Matrix<T>::width() const { return dims.getCol(); }

template<class T>
int Matrix<T>::size() const { return height() * width(); }

template<class T>
Matrix<T> Matrix<T>::Identity(int size, T values) {//TODO:should we use & in here? if not so we need to change transpose()
    if (size <= 0) {
        throw Matrix<T>::IllegalInitialization();
    }
    Dimensions dims(size, size);
    Matrix i_matrix(dims);//todo: shouldn't we need to allocate on the stack?
    for (int i = 0; i < size; i++) {
        i_matrix(i, i) = values;
    }
    return i_matrix;
}

template<class T>
Matrix<T>& Matrix<T>::transpose() const {
    Dimensions transpose_dims(width(), height());
    Matrix transpose_matrix(transpose_dims);

    for (int i = 0; i < transpose_matrix.height(); i++) {
        for (int j = 0; j < transpose_matrix.width(); j++) {
            transpose_matrix(i, j) = (*this)(j, i);
        }
    }
    return transpose_matrix;
}

template<class T>
Matrix<T>& Matrix<T>::operator-(const Matrix<T>& matrix) const {
    IntMatrix* result_matrix = new IntMatrix(dims);
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*result_matrix)(i, j) = (*this)(i, j) - matrix(i, j);
        }
    }

    return *result_matrix;
}

IntMatrix& IntMatrix::operator-() const {
    IntMatrix* result_matrix = new IntMatrix(dims);
    *result_matrix -= *this;

    return *result_matrix;
}

// TODO: Consider merging w/ operator-(matrix) somehow
IntMatrix& IntMatrix::operator+(const IntMatrix& matrix) const {
    IntMatrix* result_matrix = new IntMatrix(dims);
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*result_matrix)(i, j) = (*this)(i, j) + matrix(i, j);
        }
    }
    return *result_matrix;
}

IntMatrix& IntMatrix::operator+(int scalar) const {
    IntMatrix* result_matrix = new IntMatrix(*this);
    return (*result_matrix) += scalar;
}

IntMatrix& mtm::operator+(int scalar, const IntMatrix& matrix_b) {
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

    for (iterator it_this = this->begin(), it_other = matrix.begin();
         it_other != matrix.end(); it_other++, it_this++) {
        *it_this = *it_other;
    }

    return *this;
}

IntMatrix& IntMatrix::operator>(int num) const {
    IntMatrix* result = new IntMatrix(*this);

    for (iterator it_result = this->begin(), it_this = this->begin();
         it_this != this->end(); it_this++, it_result++) {
        *it_result = *it_this > num ? 1 : 0;
    }

    return *result;
}

IntMatrix& IntMatrix::operator<(int num) const {
    IntMatrix* result = new IntMatrix(*this);

    for (iterator it_result = this->begin(), it_this = this->begin();
         it_this != this->end(); it_this++, it_result++) {
        *it_result = *it_this < num ? 1 : 0;
    }

    return *result;
}

IntMatrix& IntMatrix::operator>=(int num) const {
    IntMatrix* ones = new IntMatrix(dims, 1);
    IntMatrix& result = (*ones) - (*this < num);
    delete ones;
    return result;
}

IntMatrix& IntMatrix::operator<=(int num) const {
    IntMatrix* ones = new IntMatrix(dims, 1);
    IntMatrix& result = (*ones) - (*this > num);
    delete ones;
    return result;
}

IntMatrix& IntMatrix::operator!=(int num) const {
    IntMatrix* ones = new IntMatrix(dims, 1);
    IntMatrix& result = (*ones) - (*this == num);
    delete ones;
    return result;
}

IntMatrix& IntMatrix::operator==(int num) const {
    IntMatrix* result = new IntMatrix(*this);

    for (iterator it_result = this->begin(), it_this = this->begin();
         it_this != this->end(); it_this++, it_result++) {
        *it_result = *it_this == num ? 1 : 0;
    }

    return *result;
}

IntMatrix& IntMatrix::operator==(const IntMatrix& matrix) const {
    IntMatrix* result = new IntMatrix(*this);

    for (iterator it_result = this->begin(), it_this = this->begin(),
                 it_other = matrix.begin();
         it_this != this->end(); it_this++, it_result++, it_other++) {
        *it_result = *it_this == *it_other ? 1 : 0;
    }

    return *result;
}

bool mtm::any(const IntMatrix& matrix) {
    for (IntMatrix::iterator it = matrix.begin(); it != matrix.end(); it++) {
        if (*it != 0) {
            return true;
        }
    }

    return false;
}

bool mtm::all(const IntMatrix& matrix) {
    for (IntMatrix::iterator it = matrix.begin(); it != matrix.end(); it++) {
        if (*it == 0) {
            return false;
        }
    }

    return true;
}