#include <bits/stdc++.h>
using namespace std;

class BigInt {
private:
    vector<int> digits;
    bool isNegative = false;

    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            isNegative = false; // If the number is zero, it should not be negative
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

        for (int i = a.digits.size() - 1; i >= 0; --i) {
            if (a.digits[i] != b.digits[i])
                return a.digits[i] > b.digits[i];
        }
        return false;
    }

public:
    // Constructors
    BigInt() : digits(1, 0) {}
    BigInt(const string& num) {
        isNegative = (num[0] == '-');
        int startIndex = isNegative ? 1 : 0;
        for (int i = num.size() - 1; i >= startIndex; --i) {
            if (isdigit(num[i]))
                digits.push_back(num[i] - '0');
        }
        removeLeadingZeros();
    }

    // Addition
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

    // Subtraction
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

    // Multiplication
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

    // Comparison
    bool operator<(const BigInt& other) const {
        if (isNegative != other.isNegative)
            return isNegative;

        if (digits.size() != other.digits.size())
            return isNegative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return isNegative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator==(const BigInt& other) const {
        return digits == other.digits && isNegative == other.isNegative;
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