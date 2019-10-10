#include <iostream>
#include <chrono>
#include <cstdlib>

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us =
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};

class Matrix
{
    int **matrix = nullptr;
    int *memory = nullptr;
public:
    int size;
    Matrix(int matrix_size) : size(matrix_size)
    {
        memory = new int[matrix_size * matrix_size];
        matrix = new int*[matrix_size];
        for (int i = 0; i < matrix_size; i++) {
            matrix[i] = memory + i * matrix_size;
        }
    }
    ~Matrix()
    {
        delete[] matrix;
        delete[] memory;
    }
    int *operator[](int i)
    {
        return matrix[i];
    }
};

enum {
    ARR_SIZE = 10000
};

void fast_treversing(Matrix &arr)
{
    Timer t;
    volatile int sum = 0;
    for (int i = 0; i < arr.size; i++) {
        for (int j = 0; j < arr.size; j++) {
            sum += arr[i][j];
        }
    }
}

void slow_treversing(Matrix &arr) {
    Timer t;
    volatile int sum = 0;
    for (int i = 0; i < arr.size; i++) {
        for (int j = 0; j < arr.size; j++) {
            sum += arr[j][i];
        }
    }
}

int main()
{
    srand(time(NULL));
    Matrix arr(ARR_SIZE);
    for (int i = 0; i < arr.size; i++) {
        for (int j = 0; j < arr.size; j++) {
            arr[i][j]= rand();
        }
    }
    std::cout << "Array size:\t\t" << ARR_SIZE << std::endl;
    std::cout << "Fast treversing time:\t";
    fast_treversing(arr);
    std::cout << "Slow treversing time:\t";
    slow_treversing(arr);
    return 0;
}
