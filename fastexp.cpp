#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

template <typename T>
T fastexp(T base, T exp, T mod = MOD) {
    T res = 1;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int b, p, m;
}