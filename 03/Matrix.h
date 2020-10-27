#include <iostream>

#pragma once

class ProxyMatrix {
    size_t col_n_;
    int * col_;
    public:
        ProxyMatrix(size_t col_n, int * col);
    int & operator[](size_t ind) const;
    ~ProxyMatrix();
};

class Matrix {
    size_t row_, column_;
    int ** buffer_;
    public:
        Matrix(size_t row = 7, size_t column = 5);
    size_t getRows() const;
    size_t getColumns() const;
    ProxyMatrix operator[](size_t index) const;
    Matrix & operator *= (int mult);
    friend std::ostream & operator << (std::ostream & ostream,
        const Matrix & matr);
    Matrix operator + (const Matrix & add) const;
    bool operator == (const Matrix & add) const;
    bool operator != (const Matrix & add) const;
    Matrix & operator = (const Matrix & elem);
    ~Matrix();
};