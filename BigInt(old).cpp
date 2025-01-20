#include <bits/stdc++.h>
using namespace std;

class BigInt { // experimental
private:
    vector<int> digits;
    vector<bool> binaryDigits;
    bool isNegative = false;

    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            isNegative = false;
    }

    // Helper functions for absolute addition and subtraction
    static BigInt addAbs(const BigInt& a, const BigInt& b) {
        BigInt result;
        result.digits.clear();
        int carry = 0, sum;
        size_t maxSize = max(a.digits.size(), b.digits.size());

        for (size_t i = 0; i < maxSize || carry; ++i) {
            sum = carry;
            if (i < a.digits.size()) sum += a.digits[i];
            if (i < b.digits.size()) sum += b.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }

        return result;
    }

    static BigInt subAbs(const BigInt& a, const BigInt& b) {
        BigInt result;
        result.digits.clear();
        int borrow = 0, diff;

        for (size_t i = 0; i < a.digits.size(); ++i) {
            diff = a.digits[i] - borrow - (i < b.digits.size() ? b.digits[i] : 0);
            borrow = (diff < 0) ? 1 : 0;
            result.digits.push_back((diff + 10) % 10);
        }

        result.removeLeadingZeros();
        return result;
    }

    static bool absGreaterThan(const BigInt& a, const BigInt& b) {
        if (a.digits.size() != b.digits.size())
            return a.digits.size() > b.digits.size();

        for (int i = a.digits.size() - 1; i >= 0; --i)
            if (a.digits[i] != b.digits[i])
                return a.digits[i] > b.digits[i];

        return false;
    }

public:
    // Default constructor
    BigInt() : digits(1, 0) {}

    // String constructor
    BigInt(const string& num) {
        isNegative = (num[0] == '-');
        int startIndex = isNegative ? 1 : 0;
        for (int i = num.size() - 1; i >= startIndex; --i)
            if (isdigit(num[i]))
                digits.push_back(num[i] - '0');
        removeLeadingZeros();
    }

    // Templated constructor for various numeric types
    template<typename T, typename = enable_if_t<is_arithmetic_v<T>>>
    BigInt(T num) {
        // Handle double or float -> truncate
        if constexpr (is_floating_point_v<T>) {
            if (num < 0) {
                isNegative = true;
                num = -num;
            }
            num = floor(num);
        }
        else {
            if (num < 0) {
                isNegative = true;
                num = -num;
            }
        }
        if (num == 0) {
            digits.push_back(0);
        } else {
            while (num > 0) {
                digits.push_back(static_cast<int>(num) % 10);
                num = static_cast<int>(num) / 10;
            }
        }
        removeLeadingZeros();
    }

    // Conversion operator for various numeric types
    template <typename T>
    operator T() const {
        T result = 0;
        T base = 1;

        for (size_t i = 0; i < digits.size(); ++i)
            result += digits[i] * base;
            base *= 10;

        if (isNegative)
            result = -result;
        return result;
    }

    // Conversion operator to string
    operator string() const {
        string result;
        if (isNegative && !(digits.size() == 1 && digits[0] == 0))
            result += '-';
        for (int i = digits.size() - 1; i >= 0; --i)
            result += to_string(digits[i]);
        return result;
    }

    // Arithmetic operators
    BigInt operator+(const BigInt& other) const {
        if (isNegative == other.isNegative) {
            BigInt result = addAbs(*this, other);
            result.isNegative = isNegative;
            return result;
        } else if (absGreaterThan(*this, other)) {
            BigInt result = subAbs(*this, other);
            result.isNegative = isNegative;
            return result;
        } else {
            BigInt result = subAbs(other, *this);
            result.isNegative = other.isNegative;
            return result;
        }
    }

    BigInt operator-(const BigInt& other) const {
        if (isNegative != other.isNegative) {
            BigInt result = addAbs(*this, other);
            result.isNegative = isNegative;
            return result;
        } else if (absGreaterThan(*this, other)) {
            BigInt result = subAbs(*this, other);
            result.isNegative = isNegative;
            return result;
        } else {
            BigInt result = subAbs(other, *this);
            result.isNegative = !other.isNegative;
            return result;
        }
    }

    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.assign(digits.size() + other.digits.size(), 0);

        for (size_t i = 0; i < digits.size(); ++i) {
            for (size_t j = 0; j < other.digits.size(); ++j) {
                result.digits[i + j] += digits[i] * other.digits[j];
                if (result.digits[i + j] >= 10) {
                    result.digits[i + j + 1] += result.digits[i + j] / 10;
                    result.digits[i + j] %= 10;
                }
            }
        }

        result.isNegative = (isNegative != other.isNegative);
        result.removeLeadingZeros();
        return result;
    }

    // Comparison operators
    bool operator==(const BigInt& other) const {
        // Special case: both are zero, return true
        if (digits.size() == 1 && digits[0] == 0 && other.digits.size() == 1 && other.digits[0] == 0)
            return true;
        return digits == other.digits && isNegative == other.isNegative;
    }

    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }

    bool operator<(const BigInt& other) const {
        if (isNegative != other.isNegative)
            return isNegative;

        if (digits.size() != other.digits.size())
            return isNegative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();

        for (int i = digits.size() - 1; i >= 0; --i)
            if (digits[i] != other.digits[i])
                return isNegative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];

        return false;
    }

    bool operator<=(const BigInt& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const BigInt& other) const {
        return !(*this <= other);
    }

    bool operator>=(const BigInt& other) const {
        return !(*this < other);
    }

    // Overloaded comparison operators for other numeric types
    template <typename T>
    bool operator==(const T& other) const {
        return *this == BigInt(other);
    }

    template <typename T>
    bool operator!=(const T& other) const {
        return *this != BigInt(other);
    }

    template <typename T>
    bool operator<(const T& other) const {
        return *this < BigInt(other);
    }

    template <typename T>
    bool operator<=(const T& other) const {
        return *this <= BigInt(other);
    }

    template <typename T>
    bool operator>(const T& other) const {
        return *this > BigInt(other);
    }

    template <typename T>
    bool operator>=(const T& other) const {
        return *this >= BigInt(other);
    }

    // Increment and decrement operators
    BigInt& operator++() {
        *this = *this + BigInt("1");
        return *this;
    }

    BigInt operator++(int) {
        BigInt temp = *this;
        *this = *this + BigInt("1");
        return temp;
    }

    BigInt& operator--() {
        *this = *this - BigInt("1");
        return *this;
    }

    BigInt operator--(int) {
        BigInt temp = *this;
        *this = *this - BigInt("1");
        return temp;
    }

    // I gave up bitwise operators

    // Compound assignment operators
    BigInt& operator+=(const BigInt& other) {
        *this = *this + other;
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        *this = *this - other;
        return *this;
    }

    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
    }

    // Negation operator
    BigInt operator-() const {
        BigInt result = *this;
        if (result.digits.size() != 1 || result.digits[0] != 0)
            result.isNegative = !result.isNegative;
        return result;
    }

    // Input/Output
    friend istream& operator>>(istream& in, BigInt& num) {
        string s;
        in >> s;
        num = BigInt(s);
        return in;
    }

    friend ostream& operator<<(ostream& out, const BigInt& num) {
        if (num.isNegative && !(num.digits.size() == 1 && num.digits[0] == 0))
            out << '-';
        for (int i = num.digits.size() - 1; i >= 0; --i)
            out << num.digits[i];
        return out;
    }
};

int main() {
    
}