#include "SMatrix.h"

// Default constructor: empty (order 0) square matrix
SMatrix::SMatrix()
{
    m = new Matrix();
}

// Order n matrix filled with zeros
// Invalid order (zero or negative) -> default empty matrix (Matrix handles this)
SMatrix::SMatrix(int n)
{
    m = new Matrix(n, n);
}

// Wraps an existing Matrix (deep copy)
// Non-square matrix -> default empty matrix
SMatrix::SMatrix(const Matrix& other)
{
    if (other.getRows() == other.getColums())
        m = new Matrix(other);
    else
        m = new Matrix();
}

// Copy constructor: deep copy of the owned Matrix
SMatrix::SMatrix(const SMatrix& other)
{
    m = new Matrix(*other.m);
}

// Destructor: SMatrix owns the Matrix, so it deletes it
SMatrix::~SMatrix()
{
    delete m;
    m = nullptr;
}

// Invalid index -> Matrix::at returns a default 0
int& SMatrix::at(int r, int c)
{
    return m->at(r, c);
}

const int& SMatrix::at(int r, int c) const
{
    return m->at(r, c);
}

int SMatrix::getRows() const
{
    return m->getRows();
}

int SMatrix::getColums() const
{
    return m->getColums();
}

void SMatrix::display() const
{
    m->display();
}

SMatrix SMatrix::Transpose() const
{
    return SMatrix(m->Transpose());
}

// Different orders -> Matrix::add returns empty -> empty SMatrix
SMatrix SMatrix::add(const SMatrix& other) const
{
    return SMatrix(m->add(*other.m));
}

// Different orders -> Matrix::multiply returns empty -> empty SMatrix
SMatrix SMatrix::multiply(const SMatrix& other) const
{
    return SMatrix(m->multiply(*other.m));
}

// New order n x n; invalid order -> unchanged (Matrix handles this)
void SMatrix::reSize(int n)
{
    m->reSize(n, n);
}