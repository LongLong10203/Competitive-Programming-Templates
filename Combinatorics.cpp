#include <bits/stdc++.h>
using namespace std;

class Combinatorics {
private:
    vector<long long> factMemo;
    vector<vector<long long>> nCrMemo;
    long long MOD;

    long long fact(int n) {
        if (n == 0 || n == 1) return 1;
        if (factMemo[n] != -1) return factMemo[n];
        return factMemo[n] = (n * fact(n - 1)) % MOD;
    }

    long long _nCr(int n, int r) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (nCrMemo[n][r] != -1) return nCrMemo[n][r];
        return nCrMemo[n][r] = (fact(n) * modInverse(fact(r)) % MOD * modInverse(fact(n - r)) % MOD) % MOD;
    }

    long long modInverse(long long a) {
        return power(a, MOD - 2);
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
        factMemo.resize(maxN + 1, -1);
        nCrMemo.resize(maxN + 1, vector<long long>(maxN + 1, -1));
    }

    long long factorial(int n) {
        return fact(n);
    }

    long long nCr(int n, int r) {
        return _nCr(n, r);
    }
};

int main() {
    
}