
#include <iostream>
#include"Matrix.h"
using namespace std;


    Matrix::Matrix() : data(nullptr), rows(0), columns(0) {}

    Matrix::Matrix(int r, int c) : data(nullptr), rows(0), columns(0)
    {
        create(r, c);
    }

    Matrix::Matrix(const Matrix& other) : data(nullptr), rows(0), columns(0)
    {
        copyFrom(other);
    }

    Matrix& Matrix::operator=(const Matrix& other)
    {
        if (this != &other)
        {
            release();
            copyFrom(other);
        }
        return *this;
    }

    Matrix::~Matrix()
    {
        release();    
    }

   
    void Matrix::create(int r, int c)
    {
        if (!validDimensions(r, c))
        {
            std::cout << "Invalid matrix size. Matrix not created.\n";
            return;
        }
        release();
        allocate(r, c);
    }

   
    void Matrix::freeMatrix() { release(); }

   
    int Matrix::getRows() const 
    { 
        return rows; 
    }
    int Matrix::getColumns() const 
    { 
        return columns; 
    }
    
    int& Matrix::getSetElement(int r, int c)
    {
        static int dummy = 0;
        if (!validIndex(r, c))
        {
            std::cout << "Matrix::getSetElement -> index out of range\n";
            dummy = 0;
            return dummy;
        }
        return data[r][c];
    }
    const int& Matrix::getSetElement(int r, int c) const
    {
        static const int dummy = 0;
        if (!validIndex(r, c))
        {
            std::cout << "Matrix::getSetElement -> index out of range\n";
            return dummy;
        }
        return data[r][c];
    }

    void Matrix::input()
    {
        if (data == nullptr)
        {
            std::cout << "Matrix is empty. Create it first.\n";
            return;
        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
            {
                std::cout << "[" << i << "][" << j << "]: ";
                std::cin >> data[i][j];
            }
    }

    void Matrix::display() const
    {
        std::cout << "Matrix Elements are:\n";
        for (int i = 0; i < rows; i++)
        {
            std::cout << i << ": ";
            for (int j = 0; j < columns; j++)
                std::cout << data[i][j] << '\t';
            std::cout << '\n';
        }
    }

    
    Matrix Matrix::add(const Matrix& other) const
    {
        Matrix result;
        if (!canAdd(*this, other))
        {
            std::cout << "Addition not possible: sizes differ.\n";
            return result;
        }
        result.allocate(rows, columns);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix Matrix::multiply(const Matrix& other) const
    {
        Matrix result;
        if (!canMultiply(*this, other))
        {
            std::cout << "Multiplication not possible: columns of first != rows of second.\n";
            return result;
        }
        result.allocate(rows, other.columns);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < other.columns; j++)
                for (int k = 0; k < columns; k++)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    void Matrix::transpose()
    {
        if (data == nullptr) return;
        int** nd = new int* [columns];
        for (int j = 0; j < columns; j++)
        {
            nd[j] = new int[rows];
            for (int i = 0; i < rows; i++)
                nd[j][i] = data[i][j];
        }
        int newRows = columns, newCols = rows;
        release();
        data = nd;
        rows = newRows;
        columns = newCols;
    }
