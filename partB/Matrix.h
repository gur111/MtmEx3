#ifndef MTMEX3_MATRIX_H
#define MTMEX3_MATRIX_H

#include <iostream>
#include <string>
#include "Auxiliaries.h"

namespace mtm {

    template<class T>
    class Matrix {
        Dimensions dims;
        T* array;

    private:
    public:
        class iterator;

        class const_iterator;

        class AccessIllegalElement;

        class IllegalInitialization;

        class DimensionMismatch;

        iterator begin() const;
        iterator end() const;
        Matrix(Dimensions dims, T initial = 0);//todo:what is the default initial value for T
        Matrix(const Matrix& matrix);
        ~Matrix();
        int size() const;
        int height() const;
        int width() const;
        static Matrix Identity(int size, T values);
        Matrix transpose() const;
        Matrix& operator=(const Matrix& matrix);
        Matrix& operator+=(T object);
        Matrix& operator-() const;
        Matrix operator-(const Matrix& matrix) const;
        Matrix operator+(const Matrix& matrix) const;
        Matrix operator+(T object) const;
        Matrix& operator-=(const Matrix& matrix);
        T& operator()(int row, int col);
        T operator()(int row, int col) const;
        Matrix<bool> operator<(T object) const;
        Matrix<bool> operator>(T object) const;
        Matrix<bool> operator<=(T object) const;
        Matrix<bool> operator>=(T object) const;
        Matrix<bool> operator!=(T object) const;
        Matrix<bool> operator==(T object) const;
        Matrix operator==(const Matrix& matrix) const;//todo:why do we need this?
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);//TODO:TODO

    };

    template<class T>
    Matrix<T> operator+(T object, const Matrix<T>& matrix_b);
    template<class T>
    bool any(const Matrix<T>& matrix);
    template<class T>
    bool all(const Matrix<T>& matrix);

    template<class T>
    Matrix<T>::Matrix(Dimensions dims, T initial) //todo: what is the default initial value for T
            : dims(dims.getRow(), dims.getCol()),
              array(new T[dims.getRow() * dims.getCol()]) {
        if (dims.getCol() <= 0 || dims.getRow() <= 0) {
            delete[] array;
            throw IllegalInitialization();
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
    Matrix<T>& Matrix<T>::operator=(const Matrix& matrix) {
        if (this == &matrix) {
            return *this;
        }

        for (iterator it_this = this->begin(), it_other = matrix.begin();//todo:iterator
             it_other != matrix.end(); it_other++, it_this++) {
            *it_this = *it_other;
        }

        return *this;
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
    Matrix<T> Matrix<T>::Identity(int size, T values) {
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

    template<class T>
    Matrix<T> Matrix<T>::transpose() const {
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
    Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix) const {
        if (this->height() != matrix.height() || this->width() != matrix.width()) {
            throw DimensionMismatch();
        }
        Matrix result_matrix(dims);//todo:changed to the new imp
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                result_matrix(i, j) = (*this)(i, j) - matrix(i, j);
            }
        }

        return result_matrix;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator-() const {//todo:do we need to return the matrix or a new one?
        Matrix* result_matrix = new Matrix(dims);
        *result_matrix -= *this;

        return *result_matrix;
    }

// TODO: Consider merging w/ operator-(matrix) somehow

    template<class T>
    Matrix<T> Matrix<T>::operator+(const Matrix& matrix) const {
        if (this->height() != matrix.height() || this->width() != matrix.width()) {
            throw DimensionMismatch();
        }
        Matrix result_matrix(dims);
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                result_matrix(i, j) = (*this)(i, j) + matrix(i, j);
            }
        }
        return result_matrix;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator+(T object) const {
        Matrix result_matrix(*this);
        return result_matrix += object;
    }

    template<class T>
    Matrix<T> mtm::operator+(T object, const Matrix<T>& matrix_b) {
        Matrix<T> result_matrix(matrix_b.dims);
        for (int i = 0; i < matrix_b.height(); i++) {
            for (int j = 0; j < matrix_b.width(); j++) {
                result_matrix(i, j) = object + matrix_b(i, j);
            }
        }
        return result_matrix;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matrix) {
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                (*this)(i, j) -= matrix(i, j);
            }
        }

        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator+=(T object) {
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                (*this)(i, j) += object;
            }
        }
        return *this;
    }

    template<class T>
    T& Matrix<T>::operator()(int row, int col) {
        if (row < 0 || col < 0 || row > height() || col > width()) {
            throw AccessIllegalElement();
        }
        return array[row * height() + col];
    }

    template<class T>
    T Matrix<T>::operator()(int row, int col) const {
        if (row < 0 || col < 0 || row > height() || col > width()) {
            throw AccessIllegalElement();
        }
        return array[row * height() + col];
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator>(T object) const {
        Matrix<bool> result(dims);
        for (iterator it_result = result.begin(), it_this = this->begin();
             it_this != this->end(); it_this++, it_result++) {
            *it_result = *it_this > object;
        }

        return result;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator<(T object) const {
        Matrix<bool> result(dims);
        for (iterator it_result = result.begin(), it_this = this->begin();
             it_this != this->end(); it_this++, it_result++) {
            *it_result = *it_this < object;
        }

        return result;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator>=(T object) const {
        Matrix<bool> ones(dims, true);
        Matrix<bool> result = ones - (*this < object);//todo:will it work on booleans?
        return result;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator<=(T object) const {
        Matrix<bool> ones(dims, true);
        Matrix<bool> result = ones - (*this > object);//todo:will it work on booleans?
        return result;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator!=(T object) const {
        Matrix<bool > ones(dims, true);
        Matrix<bool> result = ones - (*this == object);
        return result;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator==(T object) const {
        Matrix<bool> result(dims);
        for (iterator it_result = result.begin(), it_this = this->begin();
             it_this != this->end(); it_this++, it_result++) {
            *it_result = *it_this == object ? 1 : 0;
        }

        return result;
    }

    IntMatrix& IntMatrix::operator==(const IntMatrix& matrix) const {//todo: why do we need this?
        IntMatrix* result = new IntMatrix(*this);

        for (iterator it_result = this->begin(), it_this = this->begin(),
                     it_other = matrix.begin();
             it_this != this->end(); it_this++, it_result++, it_other++) {
            *it_result = *it_this == *it_other ? 1 : 0;
        }

        return *result;
    }
    template<class T>
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

    template<class T>
    class Matrix<T>::AccessIllegalElement {
        std::string what() {
            return "Mtm matrix error: An attempt to access an illegal element";
        };
    };

    template<class T>
    class Matrix<T>::IllegalInitialization {
        std::string what() {
            return "Mtm matrix error: Illegal initialization values";
        };
    };
}
#endif //MTMEX3_MATRIX_H
