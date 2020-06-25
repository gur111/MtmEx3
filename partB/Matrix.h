#ifndef MTMEX3_MATRIX_H
#define MTMEX3_MATRIX_H

#include <assert.h>

#include <iostream>
#include <string>

#include "../Auxiliaries.h"

namespace mtm {

template <class T>
class Matrix {
    Dimensions dims;
    T* array;

   public:
    // Exceptions
    class AccessIllegalElement;
    class IllegalInitialization;
    class DimensionMismatch;

    // Iterations
    class iterator;
    class const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Ctors and Dtor
    Matrix(Dimensions dims, T initial = T());
    Matrix(const Matrix& matrix);
    ~Matrix();

    // Functions (Static Methods)
    static Matrix Identity(int size);
    static Matrix Diagonal(int size, T values);

    // Methods
    int size() const;
    int height() const;
    int width() const;
    Matrix transpose() const;
    template <class Functor>
    Matrix apply(Functor op) const;

    // Operators
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator+=(T object);
    Matrix operator-() const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator+(const Matrix& matrix) const;
    Matrix operator+(T object) const;
    Matrix& operator-=(const Matrix& matrix);
    T& operator()(int row, int col);
    const T& operator()(int row, int col) const;
    Matrix<bool> operator<(T object) const;
    Matrix<bool> operator>(T object) const;
    Matrix<bool> operator<=(T object) const;
    Matrix<bool> operator>=(T object) const;
    Matrix<bool> operator!=(T object) const;
    Matrix<bool> operator==(T object) const;
    Matrix operator==(const Matrix& matrix) const;  // todo:why do we need this?
    template <class U>
    friend Matrix<U> operator+(U object, const Matrix<U>& matrix_b);
};

template <class T>
class Matrix<T>::const_iterator {
   private:
    int index;
    const Matrix<T>* matrix;
    const_iterator(const Matrix<T>* matrix, int index);

    friend class Matrix<T>;

   public:
    const T& operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
};

template <class T>
class Matrix<T>::iterator {
   private:
    int index;
    Matrix<T>* matrix;
    iterator(Matrix<T>* matrix, int index);

    friend class Matrix;

   public:
    T& operator*() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;
    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;
};

template <class T>
Matrix<T> operator+(T object, const Matrix<T>& matrix_b);
template <class T>
bool any(const Matrix<T>& matrix);
template <class T>
bool all(const Matrix<T>& matrix);

template <class T>
Matrix<T>::Matrix(Dimensions dims, T initial)
    : dims(dims.getRow(), dims.getCol()) {
    if (dims.getCol() <= 0 || dims.getRow() <= 0) {
        throw IllegalInitialization(dims);
    }

    array = new T[dims.getRow() * dims.getCol()];

    for (int i = 0; i < dims.getRow() * dims.getCol(); i++) {
        array[i] = initial;
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix& matrix)
    : dims(matrix.height(), matrix.width()), array(new T[matrix.size()]) {
    (*this) = matrix;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& matrix) {
    if (this == &matrix) {
        return *this;
    }
    iterator it_this = this->begin();

    for (const_iterator it_other = matrix.begin();  // todo:iterator
         it_other != matrix.end(); it_other++, it_this++) {
        *it_this = *it_other;
    }

    return *this;
}

template <class T>
Matrix<T>::~Matrix() {
    delete[] array;
}

template <class T>
int Matrix<T>::height() const {
    return dims.getRow();
}

template <class T>
int Matrix<T>::width() const {
    return dims.getCol();
}

template <class T>
int Matrix<T>::size() const {
    return height() * width();
}

template <class T>
Matrix<T> Matrix<T>::Identity(int size) {
    return Matrix<T>::Diagonal(size, 1);
}

template <class T>
Matrix<T> Matrix<T>::Diagonal(int size, T values) {
    if (size <= 0) {
        throw IllegalInitialization();
    }
    Dimensions dims(size, size);
    Matrix i_matrix(dims);
    for (int i = 0; i < size; i++) {
        i_matrix(i, i) = values;
    }
    return i_matrix;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
    Dimensions transpose_dims(width(), height());
    Matrix transpose_matrix(transpose_dims);

    for (int i = 0; i < transpose_matrix.size(); i++) {
        transpose_matrix.array[i] = this->array[i];
    }
    return transpose_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix) const {
    if (this->height() != matrix.height() || this->width() != matrix.width()) {
        throw DimensionMismatch(*this, matrix);
    }
    Matrix result_matrix(dims);  // TODO: changed to the new imp
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            result_matrix(i, j) = (*this)(i, j) - matrix(i, j);
        }
    }

    return result_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix<T> result_matrix(dims);
    result_matrix -= *this;

    return result_matrix;
}

// TODO: Consider merging w/ operator-(matrix) somehow

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix& matrix) const {
    if (this->height() != matrix.height() || this->width() != matrix.width()) {
        throw DimensionMismatch(*this, matrix);
    }
    Matrix result_matrix(dims);
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            result_matrix(i, j) = (*this)(i, j) + matrix(i, j);
        }
    }
    return result_matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator+(T object) const {
    Matrix<T> result = *this + Matrix<T>((*this).dims, object);
    return result;
}

template <class T>
Matrix<T> operator+(T object, const Matrix<T>& matrix_b) {
    Matrix<T> result_matrix(matrix_b.dims);
    for (int i = 0; i < matrix_b.height(); i++) {
        for (int j = 0; j < matrix_b.width(); j++) {
            result_matrix(i, j) = object + matrix_b(i, j);
        }
    }
    return result_matrix;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matrix) {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*this)(i, j) -= matrix(i, j);
        }
    }

    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(T object) {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            (*this)(i, j) += object;
        }
    }
    return *this;
}

template <class T>
T& Matrix<T>::operator()(int row, int col) {
    if (row < 0 || col < 0 || row >= height() || col >= width()) {
        throw AccessIllegalElement();
    }
    return array[row * height() + col];
}

template <class T>
const T& Matrix<T>::operator()(int row, int col) const {
    if (row < 0 || col < 0 || row >= height() || col >= width()) {
        throw AccessIllegalElement();
    }
    return array[row * height() + col];
}

template <class T>
Matrix<bool> Matrix<T>::operator>(T object) const {
    Matrix<bool> result(dims);
    for (iterator it_result = result.begin(), it_this = this->begin();
         it_this != this->end(); it_this++, it_result++) {
        *it_result = *it_this > object;
    }

    return result;
}

template <class T>
Matrix<bool> Matrix<T>::operator<(T object) const {
    Matrix<bool> result(dims);
    const_iterator it_this = this->begin();

    for (Matrix<bool>::iterator it_result = result.begin();
         it_this != this->end(); it_this++, it_result++) {
        *it_result = *it_this < object;
    }

    return result;
}

template <class T>
Matrix<bool> Matrix<T>::operator>=(T object) const {
    Matrix<bool> ones(dims, true);
    Matrix<bool> result =
        ones - (*this < object);  // todo:will it work on booleans?
    return result;
}

template <class T>
Matrix<bool> Matrix<T>::operator<=(T object) const {
    Matrix<bool> ones(dims, true);
    Matrix<bool> result =
        ones - (*this > object);  // todo:will it work on booleans?
    return result;
}

template <class T>
Matrix<bool> Matrix<T>::operator!=(T object) const {
    Matrix<bool> ones(dims, true);
    // Subtraction between booleans is well defined (and is infact XOR)
    Matrix<bool> result = ones - (*this == object);
    return result;
}

template <class T>
Matrix<bool> Matrix<T>::operator==(T object) const {
    Matrix<bool> result(dims);
    Matrix<bool>::iterator it_result = result.begin();

    for (const_iterator it_this = this->begin(); it_this != this->end();
         it_this++, it_result++) {
        *it_result = *it_this == object ? 1 : 0;
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator==(const Matrix& matrix) const {
    Matrix<T> result(*this);

    for (iterator it_result = result.begin(), it_this = this->begin(),
                  it_other = matrix.begin();
         it_this != this->end(); it_this++, it_result++, it_other++) {
        *it_result = *it_this == *it_other ? 1 : 0;
    }

    return result;
}

template <class T>
bool any(const Matrix<T>& matrix) {
    for (typename Matrix<T>::const_iterator it = matrix.begin();
         it != matrix.end(); it++) {
        if (*it != 0) {
            return true;
        }
    }

    return false;
}

template <class T>
bool all(const Matrix<T>& matrix) {
    for (typename Matrix<T>::const_iterator it = matrix.begin();
         it != matrix.end(); it++) {
        if (*it == 0) {
            return false;
        }
    }

    return true;
}

template <class T>
template <class Functor>
Matrix<T> Matrix<T>::apply(Functor operation) const {
    Matrix<T> result = *this;
    typename Matrix<T>::iterator it_result = result.begin();

    for (T curr : *this) {
        *it_result = operation(curr);
        it_result++;
    }

    return result;
}

template <class T>
class Matrix<T>::AccessIllegalElement : public Exception {
    const std::string error =
        "Mtm matrix error: An attempt to access an illegal element";

   public:
    std::string what() { return error; };
};

template <class T>
class Matrix<T>::IllegalInitialization : public Exception {
    std::string error = "Mtm matrix error: Illegal initialization values";

   public:
    IllegalInitialization() = default;
    IllegalInitialization(Dimensions dim) {
        error += ". Unknown dimensions: " + dim.toString();
    }

    std::string what() { return error; };
};

template <class T>
class Matrix<T>::DimensionMismatch : public Exception {
    const std::string error;

   public:
    DimensionMismatch(const Matrix<T>& first, const Matrix<T>& second)
        : error("Mtm matrix error: Dimensions mismatch: (" +
                std::to_string(first.height()) + "," +
                std::to_string(first.width()) + ") (" +
                std::to_string(second.height()) + "," +
                std::to_string(second.width()) + ")") {}

    std::string what() { return error; };
};

template <class T>
Matrix<T>::const_iterator::const_iterator(const Matrix<T>* matrix, int index)
    : matrix(matrix), index(index) {}

template <class T>
const T& Matrix<T>::const_iterator::operator*() const {
    if (index < 0 or index >= matrix->size()) {
        throw AccessIllegalElement();
    }
    return this->matrix->array[index];
}

template <class T>
typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++() {
    ++index;
    return *this;
}

template <class T>
typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int) {
    const_iterator result = *this;
    ++*this;
    return result;
}

template <class T>
bool Matrix<T>::const_iterator::operator==(const const_iterator& it) const {
    assert(matrix == it.matrix);
    return index == it.index;
}

template <class T>
bool Matrix<T>::const_iterator::operator!=(const const_iterator& it) const {
    return not(*this == it);
}

template <class T>
Matrix<T>::iterator::iterator(Matrix<T>* matrix, int index)
    : matrix(matrix), index(index) {}

template <class T>
T& Matrix<T>::iterator::operator*() const {
    if (index < 0 or index >= matrix->size()) {
        throw AccessIllegalElement();
    }
    return matrix->array[index];
}

template <class T>
typename Matrix<T>::iterator& Matrix<T>::iterator::operator++() {
    ++index;
    return *this;
}

template <class T>
typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int) {
    iterator result = *this;
    ++*this;
    return result;
}

template <class T>
bool Matrix<T>::iterator::operator==(const iterator& another) const {
    assert(matrix == another.matrix);
    return index == another.index;
}

template <class T>
bool Matrix<T>::iterator::operator!=(const iterator& another) const {
    return not(*this == another);
}

template <class T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const {
    return const_iterator(this, 0);
}

template <class T>
typename Matrix<T>::const_iterator Matrix<T>::end() const {
    return const_iterator(this, size());
}

template <class T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    return iterator(this, 0);
}

template <class T>
typename Matrix<T>::iterator Matrix<T>::end() {
    return iterator(this, size());
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    return printMatrix(os, matrix.begin(), matrix.end(), matrix.width());
}

}  // namespace mtm

#endif  // MTMEX3_MATRIX_H
