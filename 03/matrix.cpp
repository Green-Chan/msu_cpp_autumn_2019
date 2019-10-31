#include <cstdlib>
#include <stdexcept>
#include "matrix.h"

Matrix::Matrix(size_t rows_num, size_t columns_num) {
    rows_n = rows_num;
    columns_n = columns_num;
    matrix = static_cast<int32_t *> (std::malloc(rows_n * columns_n * sizeof(int32_t));
    if (!matrix) {
        rows_n = columns_n = 0;
    }
}
Matrix::~Matrix() {
    if (matrix) {
        free(matrix);
    }
}

size_t Matrix::rows() const {
    return rows_n;
}

size_t Matrix::columns() const {
    return columns_n;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows_n != other.rows() || columns_n != other.columns()) {
        return false;
    }
    for (size_t i = 0; i < rows_n; i++) {
        for (size_t j = 0; j < columns_n; j++) {
            if ((*this)[i][j] != other[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

const Row Matrix::operator[](size_t i) const {
    if (i >= rows_n) {
        throw std::out_of_range("");
    }
    return Row(matrix + i * columns_n, columns_n);
}

Row Matrix::operator[](size_t i) {
    if (i >= rows_n) {
        throw std::out_of_range("");
    }
    return Row(matrix + i * columns_n, columns_n);
}

Matrix& Matrix::operator*=(const int other) {
    for (size_t i = 0; i < rows_n * columns_n; i++) {
        matrix[i] *= other;
    }
    return *this;
}

Row::Row(int32_t *row_ptr, size_t row_size) {
    row = row_ptr;
    size = row_size;
}

const int32_t& Row::operator[](size_t i) const {
    if (i >= size) {
        throw std::out_of_range("");
    }
    return row[i];
}

int32_t& Row::operator[](size_t i) {
    if (i >= size) {
        throw std::out_of_range("");
    }
    return row[i];
}
