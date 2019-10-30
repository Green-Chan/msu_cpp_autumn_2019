#include <iostream>
#include "matrix.h"

int main() {
    bool no_errors = 1;
    Matrix a = Matrix(1, 2);
    if (a.rows() != 1 || a.columns() != 2) {
        no_errors = 0;
        std::cout << "error on test 1" << std::endl;
    }
    a[0][0] = 1;
    a[0][1] = 1;
    Matrix b = Matrix(1, 2);
    b[0][0] = 1;
    b[0][1] = 1;
    if (a != b) {
        no_errors = 0;
        std::cout << "error on test 2" << std::endl;
    }
    b[0][0] = 2;
    if (a == b) {
        no_errors = 0;
        std::cout << "error on test 3" << std::endl;
    }
    b[0][1] = 2;
    a *= 2;
    if (a != b) {
        no_errors = 0;
        std::cout << "error on test 4" << std::endl;
    }
    Matrix c = Matrix(2, 1);
    c[0][0] = 2;
    c[1][0] = 2;
    if (a == c) {
        no_errors = 0;
        std::cout << "error on test 5" << std::endl;
    }
    if (no_errors) {
        std::cout << "no errors" << std::endl;
    }
}
