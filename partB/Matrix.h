#ifndef MTMEX3_MATRIX_H
#define MTMEX3_MATRIX_H
#include <iostream>
#include <string>
#include "Auxiliaries.h"

namespace mtm{

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
        Matrix& transpose() const;
        Matrix& operator=(const Matrix& matrix);
        Matrix& operator+=(int scalar);
        Matrix& operator-() const;
        Matrix& operator-(const Matrix& matrix) const;
        Matrix& operator+(const Matrix& matrix) const;
        Matrix& operator+(int scalar) const;
        Matrix& operator-=(const Matrix& matrix);
        int& operator()(int row, int col);
        int& operator()(int row, int col) const;
        Matrix& operator<(int num) const;
        Matrix& operator>(int num) const;
        Matrix& operator<=(int num) const;
        Matrix& operator>=(int num) const;
        Matrix& operator!=(int num) const;
        Matrix& operator==(int num) const;
        Matrix& operator==(const Matrix& matrix) const;
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    };

    template <class T>
    class Matrix<T>::DimensionMismatch{
        std::string what(Matrix<T> first, Matrix<T> second){
            return "Mtm matrix error: Dimensions mismatch: (" + std::to_string(first.getRow)+","+
                   std::to_string(first.getCol)+") (" + std::to_string(second.getRow) + ","+
                   std::to_string(second.getCol)+") ";
        };
    };

    template <class T>
    class Matrix<T>::AccessIllegalElement{
        std::string what(){
            return "Mtm matrix error: An attempt to access an illegal element";
        };
    };

    template <class T>
    class Matrix<T>::IllegalInitialization{
        std::string what(){
            return "Mtm matrix error: Illegal initialization values";
        };
    };
}
#endif //MTMEX3_MATRIX_H
