#pragma ones
#include <iostream>
class BigInt
{
public:
    BigInt();
    BigInt(long long value);
    BigInt(const BigInt &value);
    BigInt(BigInt&& value);
    ~BigInt();
    BigInt &operator=(const BigInt &value);
    BigInt &operator=(BigInt&& value);
    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
    BigInt operator+(const BigInt& value) const;
    BigInt operator-(const BigInt& value) const;
    BigInt operator-() const;
    bool operator==(const BigInt& value) const;
    bool operator!=(const BigInt& value) const;
    bool operator>=(const BigInt& value) const;
    bool operator<=(const BigInt& value) const;
    bool operator<(const BigInt& value) const;
    bool operator>(const BigInt& value) const;
private:
    int *arr;
    size_t num_size;
    BigInt(int *a, size_t s);
};
