#include <bits/stdc++.h>
using namespace std;

class i128 {
private:
    __int128_t value;

public:
    // Constructors
    i128() : value(0) {}
    i128(const __int128_t& v) : value(v) {}
    i128(int v) : value(static_cast<__int128_t>(v)) {}
    i128(long long v) : value(static_cast<__int128_t>(v)) {}

    // Conversion to __int128_t
    explicit operator __int128_t() const { return value; }

    // Conversion operators for built-in types
    operator int() const {
        if (value > numeric_limits<int>::max() || value < numeric_limits<int>::min())
            throw overflow_error("Overflow: value is too large for int");
        return static_cast<int>(value);
    }

    operator long long() const {
        if (value > numeric_limits<long long>::max() || value < numeric_limits<long long>::min())
            throw overflow_error("Overflow: value is too large for long long");
        return static_cast<long long>(value);
    }

    operator float() const {
        return static_cast<float>(value);
    }

    operator double() const {
        return static_cast<double>(value);
    }

    // Arithmetic operators
    i128 operator+(const i128& other) const { return i128(value + other.value); }
    i128 operator-(const i128& other) const { return i128(value - other.value); }
    i128 operator*(const i128& other) const { return i128(value * other.value); }
    i128 operator/(const i128& other) const {
        if (other.value == 0) throw overflow_error("Division by zero");
        return i128(value / other.value);
    }
    i128 operator%(const i128& other) const {
        if (other.value == 0) throw overflow_error("Modulo by zero");
        return i128(value % other.value);
    }

    // Compound assignment operators
    i128& operator+=(const i128& other) {
        value += other.value;
        return *this;
    }
    i128& operator-=(const i128& other) {
        value -= other.value;
        return *this;
    }
    i128& operator*=(const i128& other) {
        value *= other.value;
        return *this;
    }
    i128& operator/=(const i128& other) {
        if (other.value == 0) throw overflow_error("Division by zero");
        value /= other.value;
        return *this;
    }
    i128& operator%=(const i128& other) {
        if (other.value == 0) throw overflow_error("Modulo by zero");
        value %= other.value;
        return *this;
    }

    // Increment and decrement operators
    i128& operator++() { // Prefix increment
        ++value;
        return *this;
    }
    i128 operator++(int) { // Postfix increment
        i128 temp(*this);
        ++(*this);
        return temp;
    }
    i128& operator--() { // Prefix decrement
        --value;
        return *this;
    }
    i128 operator--(int) { // Postfix decrement
        i128 temp(*this);
        --(*this);
        return temp;
    }

    // Comparison operators
    bool operator==(const i128& other) const { return value == other.value; }
    bool operator!=(const i128& other) const { return value != other.value; }
    bool operator<(const i128& other) const { return value < other.value; }
    bool operator<=(const i128& other) const { return value <= other.value; }
    bool operator>(const i128& other) const { return value > other.value; }
    bool operator>=(const i128& other) const { return value >= other.value; }

    // Bitwise operators
    i128 operator&(const i128& other) const { return i128(value & other.value); }
    i128 operator|(const i128& other) const { return i128(value | other.value); }
    i128 operator^(const i128& other) const { return i128(value ^ other.value); }
    i128 operator~() const { return i128(~value); }
    i128 operator<<(int shift) const { return i128(value << shift); }
    i128 operator>>(int shift) const { return i128(value >> shift); }

    // Compound bitwise assignment operators
    i128& operator&=(const i128& other) {
        value &= other.value;
        return *this;
    }
    i128& operator|=(const i128& other) {
        value |= other.value;
        return *this;
    }
    i128& operator^=(const i128& other) {
        value ^= other.value;
        return *this;
    }
    i128& operator<<=(int shift) {
        value <<= shift;
        return *this;
    }
    i128& operator>>=(int shift) {
        value >>= shift;
        return *this;
    }

    // Input/Output operators
    friend ostream& operator<<(ostream& os, const i128& obj) {
        if (obj.value == 0) {
            os << '0';
            return os;
        }

        __int128_t tmp = obj.value;
        bool negative = tmp < 0;
        if (negative) {
            os << '-';
            tmp = -tmp;
        }

        string str;
        while (tmp > 0) {
            str += '0' + (tmp % 10);
            tmp /= 10;
        }
        reverse(str.begin(), str.end());
        os << str;

        return os;
    }

    friend istream& operator>>(istream& is, i128& obj) {
        string str;
        is >> str;
        bool negative = (str[0] == '-');
        obj.value = 0;
        for (size_t i = (negative ? 1 : 0); i < str.size(); ++i) {
            if (!isdigit(str[i])) {
                is.setstate(ios::failbit);
                return is;
            }
            obj.value = obj.value * 10 + (str[i] - '0');
        }
        if (negative) {
            obj.value = -obj.value;
        }
        return is;
    }
};

int main() {
    
}