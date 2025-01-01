#include <bits/stdc++.h>
using namespace std;

template <typename T>
class CRT {
public:
    void add(T remainder, T modulo) {
        equations.emplace_back(remainder, modulo);
    }

    T calculate() {
        T x = 0, M = 1;
        for (const auto& [remainder, modulo] : equations) {
            M *= modulo;
        }
        for (const auto& [remainder, modulo] : equations) {
            T Mi = M / modulo;
            x += remainder * Mi * modInverse(Mi, modulo);
            x %= M;
        }
        return (x + M) % M;
    }

private:
    vector<pair<T, T>> equations;

    T modInverse(T a, T m) {
        T m0 = m, t, q;
        T x0 = 0, x1 = 1;
        if (m == 1) return 0;
        while (a > 1) {
            q = a / m;
            t = m;
            m = a % m, a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }
};

int main() {
    
}