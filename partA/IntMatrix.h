#ifndef MTMEX3_INTMATRIX_H
#define MTMEX3_INTMATRIX_H

#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm {
    class IntMatrix {
        Dimensions dims;
        int *array;
    private:
        void deleteArray();
        void assignment(const IntMatrix& matrix);

    public:
        IntMatrix(Dimensions dims, int initial = 0);
        IntMatrix(const IntMatrix& matrix);
        IntMatrix(int scalar);
        ~IntMatrix();
        int size() const;
        int height() const;
        int width() const;
        static IntMatrix Identity(int size);
        IntMatrix transpose() const;
        IntMatrix& operator=(const IntMatrix& matrix);
        IntMatrix& operator+=(const IntMatrix& matrix);
        IntMatrix& operator-();//need to check if we need to return a new matrix or change the current one
        IntMatrix operator-(const IntMatrix& matrix) const;
        IntMatrix operator<(int num) const;
        IntMatrix operator>(int num) const;
        IntMatrix operator<=(int num) const;
        IntMatrix operator>=(int num) const;
        IntMatrix operator==(int num) const;
        IntMatrix operator!=(int num) const;
        friend ostream& operator<<(ostream& os, const IntMatrix matrix);
        int& operator()(int row, int col);
        int& operator()(int row, int col) const;
    };

    IntMatrix operator+(const IntMatrix& matrix_a, const IntMatrix& matrix_b);
    bool any(IntMatrix matrix);
    bool all(IntMatrix matrix);
}
#endif //MTMEX3_INTMATRIX_H
