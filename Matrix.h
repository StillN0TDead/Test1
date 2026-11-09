#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
    int** data;
    int rows;
    int columns;

    static bool validDimensions(int r, int c) { return r > 0 && c > 0; }

    static bool canAdd(const Matrix& a, const Matrix& b)
    {
        return a.rows == b.rows && a.columns == b.columns;
    }

    static bool canMultiply(const Matrix& a, const Matrix& b)
    {
        return a.columns == b.rows;
    }

    void allocate(int r, int c)         
    {
        rows = r;
        columns = c;
        data = new int* [rows];
        for (int i = 0; i < rows; i++)
        {
            data[i] = new int[columns];
            for (int j = 0; j < columns; j++) data[i][j] = 0;
        }
    }

    void release()                      
    {
        if (data != nullptr)
        {
            for (int i = 0; i < rows; i++) delete[] data[i];
            delete[] data;
        }
        data = nullptr;
        rows = 0;
        columns = 0;
    }

    void copyFrom(const Matrix& other)   
    {
        if (other.data == nullptr) return;
        allocate(other.rows, other.columns);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                data[i][j] = other.data[i][j];
    }

    bool validIndex(int r, int c) const
    {
        return data != nullptr && r >= 0 && r < rows && c >= 0 && c < columns;
    }

public:

    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();
    void create(int r, int c);
    void freeMatrix();
    int getRows() const;
    int getColumns() const;
    int& getSetElement(int r, int c);
    const int& getSetElement(int r, int c) const;
    void input();
    void display() const;
    Matrix add(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;
    void transpose();
    
};

#endif