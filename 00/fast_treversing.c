#include <iostream>
#include <chrono>

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

enum {
    ARR_SIZE = 10000
};

int main()
{
    Timer t;
    int arr[ARR_SIZE][ARR_SIZE]
    volatile int sum = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            sum += arr[i][j];
        }
    }
    return 0;
}
