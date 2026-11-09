#include "Matrix.h"
#include <iostream>
using namespace std;

// Default constructor: empty 0x0 matrix
Matrix::Matrix()
{
    rows = 0;
    cols = 0;
    data = nullptr;
}

// Parameterized constructor: r x c matrix filled with zeros
// Invalid size (zero or negative) -> default empty 0x0 matrix
Matrix::Matrix(int r, int c)
{
    if (r <= 0 || c <= 0)
    {
        rows = 0;
        cols = 0;
        data = nullptr;
        return;
    }

    rows = r;
    cols = c;
    data = new int* [rows];

    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            data[i][j] = 0;
    }
}

// Copy constructor: deep copy
Matrix::Matrix(const Matrix& other)
{
    rows = other.rows;
    cols = other.cols;
    data = nullptr;

    if (rows > 0 && cols > 0)
    {
        data = new int* [rows];
        for (int i = 0; i < rows; i++)
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                data[i][j] = other.data[i][j];
        }
    }
    else
    {
        rows = 0;
        cols = 0;
    }
}

// Destructor
Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;
    data = nullptr;
    rows = 0;
    cols = 0;
}

// Element access (modifiable)
// Invalid index -> returns a reference to a default value 0 (writes to it are discarded)
int& Matrix::at(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
    {
        static int dummy;
        dummy = 0;
        return dummy;
    }
    return data[r][c];
}

// Element access (read-only)
// Invalid index -> returns a reference to a dummy 0
const int& Matrix::at(int r, int c) const
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
    {
        static const int dummy = 0;
        return dummy;
    }
    return data[r][c];
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getColums() const
{
    return cols;
}

void Matrix::display() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << data[i][j] << "\t";
        cout << endl;
    }
}

Matrix Matrix::Transpose() const
{
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[j][i] = data[i][j];
    return result;
}

// Dimensions differ -> returns an empty 0x0 matrix
Matrix Matrix::add(const Matrix& other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        return Matrix();
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

// cols != other.rows -> returns an empty 0x0 matrix
Matrix Matrix::multiply(const Matrix& other) const
{
    if (cols != other.rows)
    {
        return Matrix();
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.cols; j++)
        {
            int sum = 0;
            for (int k = 0; k < cols; k++)
                sum += data[i][k] * other.data[k][j];
            result.data[i][j] = sum;
        }
    return result;
}

// Resize: keeps overlapping elements, new cells are zero
// Invalid size (zero or negative) -> matrix is left unchanged
void Matrix::reSize(int newRows, int newCols)
{
    if (newRows <= 0 || newCols <= 0)
    {
        return;
    }

    int** newData = new int* [newRows];

    for (int i = 0; i < newRows; i++)
    {
        newData[i] = new int[newCols];
        for (int j = 0; j < newCols; j++)
        {
            if (i < rows && j < cols)
                newData[i][j] = data[i][j];
            else
                newData[i][j] = 0;
        }
    }

    for (int i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;

    data = newData;
    rows = newRows;
    cols = newCols;
}

Matrix Matrix::slice(int rowstart, int colstart, int rowend, int colend) const
{
	if (rowstart < 0 || colstart < 0 || rowend > rows || colend > cols || rowstart >= rowend || colstart >= colend)
	{
		return Matrix();
	}
	Matrix result(rowend - rowstart, colend - colstart);
	for (int i = 0; i < result.getRows(); i++)
		for (int j = 0; j < result.getColums(); j++)
			result.data[i][j] = data[rowstart + i][colstart +  j];
	return result;
}   