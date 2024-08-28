#include <bits/stdc++.h>
using namespace std;

class Combinatorics {
private:
    vector<long long> factMemo;
    vector<long long> invFactMemo;
    long long MOD;

    void precompute(int maxN) {
        factMemo[0] = 1;
        for (int i = 1; i <= maxN; ++i)
            factMemo[i] = (factMemo[i - 1] * i) % MOD;
        invFactMemo[maxN] = power(factMemo[maxN], MOD - 2);
        for (int i = maxN - 1; i >= 0; --i)
            invFactMemo[i] = (invFactMemo[i + 1] * (i + 1)) % MOD;
    }

    long long power(long long x, long long y) {
        long long res = 1;
        x = x % MOD;
        while (y > 0) {
            if (y & 1) res = (res * x) % MOD;
            y = y >> 1;
            x = (x * x) % MOD;
        }
        return res;
    }

public:
    Combinatorics(int maxN, long long mod) : MOD(mod) {
        factMemo.resize(maxN + 1);
        invFactMemo.resize(maxN + 1);
        precompute(maxN);
    }

    long long factorial(int n) {
        return factMemo[n];
    }

    long long nCr(int n, int r) {
        if (r > n) throw invalid_argument("r > n");
        return (factMemo[n] * invFactMemo[r] % MOD * invFactMemo[n - r] % MOD) % MOD;
    }
};

int main() {
    
}