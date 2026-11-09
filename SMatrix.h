#ifndef SMATRIX_H
#define SMATRIX_H

#include "Matrix.h"

// Square matrix wrapper: reuses Matrix (strong aggregation / composition).
// SMatrix creates its own Matrix object dynamically, owns it, and destroys it.
class SMatrix
{
    Matrix* m;

public:
    SMatrix();
    SMatrix(int);
    SMatrix(const Matrix&);
    SMatrix(const SMatrix&);
    ~SMatrix();
    int& at(int, int);
    const int& at(int, int) const;
    int getRows() const;
    int getColums() const;
    void display() const;
    SMatrix Transpose() const;
    SMatrix add(const SMatrix&) const;
    SMatrix multiply(const SMatrix&) const;
    void reSize(int);
    SMatrix slice(int, int, int, int) const;
	// many other functions
};

#endif