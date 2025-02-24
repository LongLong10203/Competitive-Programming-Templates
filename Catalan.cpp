#include <bits/stdc++.h>
using namespace std;

namespace Constants {
    constexpr int MOD = 1e9 + 7;
}

template<int _MOD> struct Modular {
    int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
    Modular() { v = 0; }
    Modular(long long _v) { v = int((-_MOD < _v && _v < _MOD) ? _v : _v % _MOD); if (v < 0) v += _MOD; }
    friend ostream& operator<<(ostream& out, const Modular& n) { return out << int(n); }
    friend istream& operator>>(istream& in, Modular& n) { long long v_; in >> v_; n = Modular(v_); return in; }

    friend bool operator==(const Modular& a, const Modular& b) { return a.v == b.v; }
    friend bool operator!=(const Modular& a, const Modular& b) { return a.v != b.v; }
    friend bool operator<(const Modular& a, const Modular& b) { return a.v < b.v; }

    Modular& operator+=(const Modular& m) { if ((v += m.v) >= _MOD) v -= _MOD; return *this; }
    Modular& operator-=(const Modular& m) { if ((v -= m.v) < 0) v += _MOD; return *this; }
    Modular& operator*=(const Modular& m) { v = int((long long)v * m.v % _MOD); return *this; }
    Modular& operator/=(const Modular& m) { return (*this) *= inv(m); }
    Modular operator-() const { return Modular(-v); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }

    friend Modular pow(Modular a, long long p) {
        Modular ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
        return ans;
    }
    friend Modular inv(const Modular& a) { assert(a.v != 0); return pow(a, _MOD - 2); }

    friend Modular operator+(Modular a, const Modular& b) { return a += b; }
    friend Modular operator-(Modular a, const Modular& b) { return a -= b; }
    friend Modular operator*(Modular a, const Modular& b) { return a *= b; }
    friend Modular operator/(Modular a, const Modular& b) { return a /= b; }
    friend Modular operator++(Modular& a, int) { Modular r = a; ++a; return r; }
    friend Modular operator--(Modular& a, int) { Modular r = a; --a; return r; }
};

template<int _MOD = Constants::MOD> struct Combinatorics {
    using Mint = Modular<_MOD>;
    vector<Mint> fact, inv_fact;
    Combinatorics(int n) : fact(n + 1), inv_fact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i;
        inv_fact[n] = inv(fact[n]);
        for (int i = n; i >= 1; --i)
            inv_fact[i - 1] = inv_fact[i] * i;
    }
    Mint nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * inv_fact[r] * inv_fact[n - r];
    }
    Mint factorial(int n) { return fact[n]; }
};

template<int _MOD = Constants::MOD> struct Catalan {
    using Mint = Modular<_MOD>;
    vector<Mint> cat;
    Catalan(int n) : cat(n + 1) {
        Combinatorics<_MOD> comb(2 * n);
        for (int i = 0; i <= n; ++i)
            cat[i] = comb.nCr(2 * i, i) / (i + 1);
    }
    Mint operator[](int i) const { return cat[i]; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    
}