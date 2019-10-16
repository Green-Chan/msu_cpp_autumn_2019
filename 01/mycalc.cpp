#include <iostream>

void
skip_spaces(char *&curr_char_ptr)
{
    while (*curr_char_ptr == ' ') {
        curr_char_ptr++;
    }
}

long long
atom (char *&curr_char_ptr, char *&error_ptr)
{
    int sgn = 1;
    if (*curr_char_ptr == '-') {
        sgn = -1;
        curr_char_ptr++;
    }
    long long atom = 0;
    if (*curr_char_ptr < '0' || *curr_char_ptr > '9') {
        if (!error_ptr) {
            error_ptr = curr_char_ptr;
        }
        return 0;
    }
    do {
        atom *= 10;
        atom += *curr_char_ptr - '0';
        curr_char_ptr++;
    } while (*curr_char_ptr >= '0' && *curr_char_ptr <= '9');
    skip_spaces(curr_char_ptr);
    return sgn * atom;
}

long long
mult(char *&curr_char_ptr, char *&error_ptr)
{
    long long mult = atom(curr_char_ptr, error_ptr);
    skip_spaces(curr_char_ptr);
    while (*curr_char_ptr == '*' || *curr_char_ptr == '/') {
        char op = *curr_char_ptr;
        curr_char_ptr++;
        skip_spaces(curr_char_ptr);
        long long multiplier = atom(curr_char_ptr, error_ptr);
        if (op == '*') {
            mult *= multiplier;
        }
        else {
            if (multiplier == 0) {
                if (!error_ptr) {
                    error_ptr = curr_char_ptr;
                }
                return 0;
            }
            mult /= multiplier;
        }
    }
    return mult;
}

long long
sum(char *&curr_char_ptr, char *&error_ptr)
{
    long long sum = mult(curr_char_ptr, error_ptr);
    skip_spaces(curr_char_ptr);
    while (*curr_char_ptr == '+' || *curr_char_ptr == '-') {
        char op = *curr_char_ptr;
        curr_char_ptr++;
        skip_spaces(curr_char_ptr);
        long long summand = mult(curr_char_ptr, error_ptr);
        if (op == '+') {
            sum += summand;
        }
        else {
            sum -= summand;
        }
    }
    return sum;
}

long long
calc_str(char *&str, char *&error_ptr)
{
    error_ptr = nullptr;
    skip_spaces(str);
    long long res = sum(str, error_ptr);
    if (*str) {
        error_ptr = str;
    }
    return res;
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "The program needs one argument" << std::endl;
        return 1;
    }
    char *curr_char_ptr = argv[1], *error_ptr;
    long long ans = calc_str(curr_char_ptr, error_ptr);
    if (!error_ptr) {
        std::cout << ans << std::endl;
    } else {
        std::cout << "The expression is incorrect" << std::endl;
    }
    return 0;
}
