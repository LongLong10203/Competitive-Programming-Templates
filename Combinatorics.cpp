#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Combinatorics {
private:
    vector<T> factMemo;
    vector<T> invFactMemo;
    T MOD;

    void precompute(int maxN) {
        factMemo[0] = 1;
        for (int i = 1; i <= maxN; ++i)
            factMemo[i] = (factMemo[i - 1] * i) % MOD;
        invFactMemo[maxN] = power(factMemo[maxN], MOD - 2);
        for (int i = maxN - 1; i >= 0; --i)
            invFactMemo[i] = (invFactMemo[i + 1] * (i + 1)) % MOD;
    }

    T power(T x, T y) {
        T res = 1;
        x = x % MOD;
        while (y > 0) {
            if (y & 1) res = (res * x) % MOD;
            y = y >> 1;
            x = (x * x) % MOD;
        }
        return res;
    }

public:
    Combinatorics(int maxN, T mod) : MOD(mod) {
        factMemo.resize(maxN + 1);
        invFactMemo.resize(maxN + 1);
        precompute(maxN);
    }

    T factorial(int n) {
        return factMemo[n];
    }

    T nCr(int n, int r) {
        if (r > n) throw invalid_argument("r > n");
        return (factMemo[n] * invFactMemo[r] % MOD * invFactMemo[n - r] % MOD) % MOD;
    }
};

int main() {
    
}