#include "bigint.h"

#include <iomanip>


enum { BASE = 1000000000, WIDTH = 9, SGN = BASE / 2 };

BigInt::BigInt() {
    num_size = 1;
    arr = new int[1];
    arr[0] = 0;
}

BigInt::BigInt(long long value) {
    unsigned long long uval = value;
    if (value < 0) {
        uval *= -1;
    }
    if (uval < BASE / 2) {
        num_size = 1;
    } else if (uval < (long long) BASE * BASE / 2) {
        num_size = 2;
    } else {
        num_size = 3;
    }
    arr = new int[num_size];
    for (size_t i = 0; i < num_size; i++) {
        arr[i] = 0;
    }
    arr[0] = 0;
    size_t i = 0;
    while (uval > 0) {
        arr[i++] = uval % BASE;
        uval /= BASE;
    }
    if (value < 0) {
        for (i = 0; i < num_size; i++) {
            arr[i] = BASE - 1 - arr[i];
        }
        char carry = 1;
        for (i = 0; i < num_size; i++) {
            arr[i] += carry;
            carry = arr[i] / BASE;
            arr[i] %= BASE;
        }
        if (num_size > 1 && arr[num_size - 1] == BASE - 1 && arr[num_size - 2] >= SGN) {
            num_size--;
            int *tmp = new int[num_size];
            std::copy(arr, arr + num_size, tmp);
            delete[] arr;
            arr = tmp;
        }
    }
}

BigInt::BigInt(const BigInt &value) {
    num_size = value.num_size;
    arr = new int[num_size];
    std::copy(value.arr, value.arr + num_size, arr);
}

BigInt::BigInt(BigInt&& value) {
    num_size = value.num_size;
    delete[] arr;
    arr = value.arr;
    value.arr = nullptr;
    value.num_size = 0;
}

BigInt::~BigInt() {
    delete[] arr;
}

BigInt& BigInt::operator=(const BigInt &value) {
    if (value == *this) {
        return *this;
    }
    num_size = value.num_size;
    delete[] arr;
    arr = new int[value.num_size];
    std::copy(value.arr, value.arr + num_size, arr);
    return *this;
}

BigInt& BigInt::operator=(BigInt&& value) {
    if (value == *this) {
        return *this;
    }
    delete[] arr;
    arr = value.arr;
    num_size = value.num_size;
    value.arr = nullptr;
    value.num_size = 0;
    return *this;
}

BigInt::BigInt(int *a, size_t s) {
    num_size = s;
    arr = new int[s];
    std::copy(a, a + s, arr);
    delete[] a;
}

std::ostream &operator<<(std::ostream &out, const BigInt &value) {
    if (value.num_size == 1 && value.arr[0] == 0) {
        out << "0";
        return out;
    }
    BigInt val = value;
    if (value.arr[value.num_size - 1] >= SGN) {
        out << '-';
        val = -value;
    }
    size_t s = val.arr[val.num_size - 1] ? val.num_size - 1 : val.num_size - 2;
    out << val.arr[s];
    for (ssize_t i = s - 1; i >= 0; i--) {
        out << std::setfill('0') << std::setw(WIDTH) << val.arr[i];
    }
    return out;
}

BigInt BigInt::operator+(const BigInt& value) const {
    if (value.num_size > num_size) {
        return value + *this;
    }
    int s1 = (arr[num_size - 1] >= SGN) * (BASE - 1);
    int s2 = (value.arr[value.num_size - 1] >= SGN) * (BASE - 1);
    int carry = 0;
    int *a = new int[num_size + 1];
    for (size_t i = 0; i < value.num_size; i++) {
        a[i] = arr[i] + value.arr[i] + carry;
        carry = a[i] / BASE;
        a[i] %= BASE;
    }
    for (size_t i = value.num_size; i < num_size; i++) {
        a[i] = arr[i] + s2 + carry;
        carry = a[i] / BASE;
        a[i] %= BASE;
    }
    a[num_size] = (s1 + s2 + carry) % BASE;
    size_t s = num_size + 1;
    if (a[num_size] >= SGN) {
        while (s > 1 && a[s - 1]== BASE - 1) {
            s--;
        }
        if (a[s - 1] < SGN) {
            s++;
        }
    } else {
        while (s > 1 && !a[s - 1]) {
            s--;
        }
        if (a[s - 1] >= SGN) {
            s++;
        }
    }
    return BigInt(a, s);
}

BigInt BigInt::operator-() const {
    int *a = new int[num_size + 1];
    size_t s = num_size;
    for (size_t i = 0; i < num_size; i++) {
        a[i] = BASE - 1 - arr[i];
    }
    char carry = 1;
    for (size_t i = 0; i < num_size; i++) {
        a[i] += carry;
        carry = a[i] / BASE;
        a[i] %= BASE;
    }
    if (arr[num_size - 1] < SGN) {
        if (num_size > 1 && a[num_size - 1] == BASE - 1 && a[num_size - 2] >= SGN) {
            s--;
        }
    } else {
        if (a[num_size - 1] >= SGN) {
            a[s++] = 0;
        }
    }
    return BigInt(a, s);
}

BigInt BigInt::operator-(const BigInt& value) const {
    return *this + (-value);
}

bool BigInt::operator==(const BigInt& value) const {
    if (num_size != value.num_size) {
        return false;
    }
    for (size_t i = 0; i < num_size; i++) {
        if (arr[i] != value.arr[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& value) const {
    return !(*this == value);
}

bool BigInt::operator>(const BigInt& value) const {
    if (arr[num_size - 1]  >= SGN) {
        if (value.arr[value.num_size - 1] >= SGN) {
            return -value > -*this;
        } else {
            return false;
        }
    } else {
        if (value.arr[value.num_size - 1] >= SGN) {
            return true;
        } else {
            if (num_size > value.num_size) {
                return true;
            } else if (num_size < value.num_size) {
                return false;
            }
            for (size_t i = 0; i < num_size; i++) {
                if (arr[i] > value.arr[i]) {
                    return true;
                } else if (arr[i] < value.arr[i]) {
                    return false;
                }
            }
            return false;
        }
    }
}

bool BigInt::operator<(const BigInt& value) const {
    return !(*this > value) && !(*this == value);
}

bool BigInt::operator<=(const BigInt& value) const {
    return !(*this > value);
}

bool BigInt::operator>=(const BigInt& value) const {
    return (*this > value) || (*this == value);
}
