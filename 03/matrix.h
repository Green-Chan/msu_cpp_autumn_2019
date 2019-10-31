#pragma ones
#include <cinttypes>

class Row
{
public:
    Row(int32_t *row_ptr, size_t row_size);
    const int32_t& operator[](size_t i) const;
    int32_t& operator[](size_t i);
private:
    int32_t *row;
    size_t size;
};

class Matrix
{
public:
    Matrix(size_t rows_num, size_t columns_num);
    ~Matrix();
    size_t rows() const;
    size_t columns() const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    const Row operator[](size_t i) const;
    Row operator[](size_t i);
    Matrix& operator*=(int other);
private:
    int32_t *matrix;
    size_t rows_n;
    size_t columns_n;
};

