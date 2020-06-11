#ifndef MTMEX3_INTMATRIX_H
#define MTMEX3_INTMATRIX_H

#include <iostream>
#include <string>

#include "Auxiliaries.h"

namespace mtm {
class IntMatrix {
    Dimensions dims;
    int* array;

   private:
    void deleteArray();
    void assignment(const IntMatrix& matrix);

   public:
    class iterator;
    class const_iterator;
    iterator begin() const;
    iterator end() const;

    IntMatrix(Dimensions dims, int initial = 0);
    IntMatrix(const IntMatrix& matrix);
    ~IntMatrix();
    int size() const;
    int height() const;
    int width() const;
    static IntMatrix& Identity(int size);
    IntMatrix& transpose() const;
    IntMatrix& operator=(const IntMatrix& matrix);
    IntMatrix& operator+=(int scalar);
    IntMatrix& operator-() const;
    IntMatrix& operator-(const IntMatrix& matrix) const;
    IntMatrix& operator+(const IntMatrix& matrix) const;
    IntMatrix& operator+(int scalar) const;
    IntMatrix& operator-=(const IntMatrix& matrix);
    int& operator()(int row, int col);
    int& operator()(int row, int col) const;
    IntMatrix& operator<(int num) const;
    IntMatrix& operator>(int num) const;
    IntMatrix& operator<=(int num) const;
    IntMatrix& operator>=(int num) const;
    IntMatrix& operator!=(int num) const;
    IntMatrix& operator==(int num) const;
    IntMatrix& operator==(const IntMatrix& matrix) const;
    friend std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix);
};

IntMatrix& operator+(int scalar, const IntMatrix& matrix_b);
bool any(IntMatrix& matrix);
bool all(IntMatrix& matrix);

class IntMatrix::const_iterator {
   private:
    int index;
    const IntMatrix* matrix;
    const_iterator(IntMatrix* matrix, int index);
    friend class IntMatrix;

   public:
    const int& operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;

    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
};

class IntMatrix::iterator {
   private:
    int index;
    const IntMatrix* matrix;
    iterator(const IntMatrix* matrix, int index);
    friend class IntMatrix;

   public:
    int& operator*() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;

    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;
};

}  // namespace mtm

#endif  // MTMEX3_INTMATRIX_H