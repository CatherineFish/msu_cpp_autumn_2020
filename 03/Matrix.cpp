#include<iostream>

#include "Matrix.h"


Matrix::Matrix(size_t row, size_t column): row_(row), column_(column) {
    buffer_ = new int * [row_];
    for (size_t i = 0; i < row_; i++) {
        buffer_[i] = new int[column_];
    }
}

Matrix::Matrix(const Matrix & elem) {
    row_ = elem.row_;
    column_ = elem.column_;
    buffer_ = new int * [row_];
    for (size_t i = 0; i < row_; i++) {
        buffer_[i] = new int[column_];
        for (size_t j = 0; j < column_; j++) {
            buffer_[i][j] = elem.buffer_[i][j];
        }
    }
}

Matrix & Matrix::operator = (const Matrix & elem) {
    this -> ~Matrix();
    new(this) Matrix(elem);
    return *this;
}

size_t Matrix::getRows() const {
    return row_;
}

size_t Matrix::getColumns() const {
    return column_;
}

ProxyMatrix Matrix::operator[](size_t index) const {
    if (index >= row_) {
        throw std::out_of_range("Row Index");
    }
    ProxyMatrix tmp(column_, buffer_[index]);
    return tmp;
}

Matrix & Matrix::operator *= (int mult) {
    for (size_t i = 0; i < row_; i++) {
        for (size_t j = 0; j < column_; j++) {
            buffer_[i][j] *= mult;
        }
    }
    return *this;
}

std::ostream & operator << (std::ostream & ostream,
    const Matrix & matr) {
    for (size_t i = 0; i < matr.row_; i++) {
        for (size_t j = 0; j < matr.column_; j++) {
            ostream << matr.buffer_[i][j] << " ";
        }
        ostream << std::endl;
    }
    return ostream;
}

Matrix Matrix::operator + (const Matrix & add) const {
    Matrix tmp(row_, column_);
    for (size_t i = 0; i < row_; i++) {
        for (size_t j = 0; j < column_; j++) {
            tmp.buffer_[i][j] = buffer_[i][j] + add.buffer_[i][j];
        }
    }
    return tmp;
}

bool Matrix::operator == (const Matrix & other) const {
    for (size_t i = 0; i < row_; i++) {
        for (size_t j = 0; j < column_; j++) {
            if (buffer_[i][j] != other.buffer_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator != (const Matrix & other) const {
    for (size_t i = 0; i < row_; i++) {
        for (size_t j = 0; j < column_; j++) {
            if (buffer_[i][j] == other.buffer_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Matrix::~Matrix() {
    for (size_t i = 0; i < row_; i++) {
        delete[] buffer_[i];
    }
    delete[] buffer_;
}

ProxyMatrix::ProxyMatrix(size_t col_n, int * col): col_n_(col_n), col_(col) {}

const int & ProxyMatrix::operator[](size_t ind) const {
    if (ind >= col_n_) {
        throw std::out_of_range("Column Index");
    }
    return col_[ind];
}

int & ProxyMatrix::operator[](size_t ind) {
    if (ind >= col_n_) {
        throw std::out_of_range("Column Index");
    }
    return col_[ind];
}

ProxyMatrix::~ProxyMatrix() =
    default;