#include <bits/stdc++.h>
using namespace std;

struct Sieve {
    vector<bool> sieve(int n) {
        vector<bool> prime(n + 1, true);
        prime[0] = prime[1] = false;
        for (int p = 2; p * p <= n; ++p)
            if (prime[p])
                for (int i = p * p; i <= n; i += p)
                    prime[i] = false;
        return prime;
    }
    vector<bool> prime;
    Sieve(int n) : prime(sieve(n)) {}
    bool isPrime(int n) {
        return prime[n];
    }
};

int main() {
    
}