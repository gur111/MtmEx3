#ifndef MTMEX3_INTMATRIX_H
#define MTMEX3_INTMATRIX_H

#include <iostream>
#include <string>

#include "Auxiliaries.h"

using std::ostream;

namespace mtm {
class IntMatrix {
    Dimensions dims;
    int** array;

   private:
    void deleteArray();
    void assignment(const IntMatrix& matrix);

   public:
    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    IntMatrix(Dimensions dims, int initial = 0);
    IntMatrix(const IntMatrix& matrix);
    IntMatrix(int scalar);
    ~IntMatrix();
    int size() const;
    int height() const;
    int width() const;
    static IntMatrix& Identity(int size);
    IntMatrix transpose() const;
    IntMatrix& operator=(const IntMatrix& matrix);
    IntMatrix& operator+=(const IntMatrix& matrix);
    IntMatrix operator-() const;
    IntMatrix operator-(const IntMatrix& matrix) const;
    IntMatrix& operator-=(const IntMatrix& matrix);
    int& operator()(int row, int col);
    int& operator()(int row, int col) const;
    IntMatrix operator<(int num) const;
    IntMatrix operator>(int num) const;
    IntMatrix operator<=(int num) const;
    IntMatrix operator>=(int num) const;
    IntMatrix operator==(int num) const;
    IntMatrix operator!=(int num) const;
    friend ostream& operator<<(ostream& os, const IntMatrix& matrix);
};

IntMatrix operator+(const IntMatrix& matrix_a, const IntMatrix& matrix_b);
bool any(IntMatrix matrix);
bool all(IntMatrix matrix);

class IntMatrix::Iterator {
    int index;
    const IntMatrix* matrix;
    Iterator(const IntMatrix* matrix, int index);
    friend class IntMatrix;

   public:
    const int& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;

    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
};

}  // namespace mtm
#endif  // MTMEX3_INTMATRIX_H
