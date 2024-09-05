#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Power {
public:
    T base;
    T exponent;

    Power() : base(0), exponent(0) {}  // Default constructor

    Power(T base, T exponent) : base(base), exponent(exponent) {}

    double logValue() const {
        return exponent * log(base);
    }

    friend bool operator==(const Power& lhs, const Power& rhs) {
        return lhs.logValue() == rhs.logValue();
    }

    friend bool operator!=(const Power& lhs, const Power& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Power& lhs, const Power& rhs) {
        return lhs.logValue() < rhs.logValue();
    }

    friend bool operator<=(const Power& lhs, const Power& rhs) {
        return lhs.logValue() <= rhs.logValue();
    }

    friend bool operator>(const Power& lhs, const Power& rhs) {
        return lhs.logValue() > rhs.logValue();
    }

    friend bool operator>=(const Power& lhs, const Power& rhs) {
        return lhs.logValue() >= rhs.logValue();
    }
};

int main() {
    
}