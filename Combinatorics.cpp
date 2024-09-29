#include <bits/stdc++.h>
using namespace std;

class Combinatorics {
private:
    int MOD;
    vector<long long> fact, inv_fact;

    void precompute(int n) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++)
            fact[i] = fact[i - 1] * i % MOD;
        inv_fact[n] = mod_pow(fact[n], MOD - 2);
        for (int i = n - 1; i >= 0; i--)
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }

public:
    Combinatorics(int n, int mod) : MOD(mod), fact(n + 1), inv_fact(n + 1) {
        precompute(n);
    }

    long long mod_pow(long long base, long long exp) {
        long long res = 1;
        while (exp > 0) {
            if (exp & 1)
                res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return res;
    }

    long long nCr(int n, int k) {
        if (k > n || k < 0) return 0;
        return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
    }

    long long nPr(int n, int k) {
        if (k > n || k < 0) return 0;
        return fact[n] * inv_fact[n - k] % MOD;
    }

    long long factorial(int n) {
        return fact[n];
    }
}; // * Note: initialise with maxN

int main() {
    
}