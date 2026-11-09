#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
    int rows, cols;
    int** data;

public:
    Matrix();
    Matrix(int, int);
    Matrix(const Matrix&);
    ~Matrix();
    int& at(int, int);
    const int& at(int, int) const;
    int getRows() const;
    int getColums() const;
    void display() const;
    Matrix Transpose() const;
    Matrix add(const Matrix&) const;
    Matrix multiply(const Matrix&) const;
    void reSize(int, int);
	Matrix slice(int, int, int, int) const;
    // many other functions
};

#endif