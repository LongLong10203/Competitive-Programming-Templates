#include <bits/stdc++.h>
using namespace std;

long long bigmod(long long base, long long exp, long long MOD) {
    long long res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % MOD;
        exp = exp >> 1;
        base = (base * base) % MOD;
    }
    return res;
}

int main() {

}