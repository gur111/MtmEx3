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
    public:
        IntMatrix(Dimensions dims, int initial = 0);
        IntMatrix(const IntMatrix& matrix);
        IntMatrix(int scalar);
        ~IntMatrix();
        IntMatrix operator=(const IntMatrix& matrix);
        static IntMatrix Identity(int size);
        int size() const;
        int height() const;
        int width() const;
        IntMatrix transpose() const;
        IntMatrix& operator+=(const IntMatrix& matrix);
        IntMatrix& operator-();//need to check if we need to return a new matrix or change the current one
        IntMatrix operator-(const IntMatrix& matrix) const;
        IntMatrix operator<(int num) const;
        IntMatrix operator>(int num) const;
        IntMatrix operator<=(int num) const;
        IntMatrix operator>=(int num) const;
        IntMatrix operator==(int num) const;
        IntMatrix operator!=(int num) const;
    };

    IntMatrix operator+(const IntMatrix& matrix_a, const IntMatrix& matrix_b);

}

#endif // MTMEX3_INTMATRIX_H
