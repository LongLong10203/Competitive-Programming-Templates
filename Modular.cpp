#include <bits/stdc++.h>
using namespace std;

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
    Modular& operator*=(const Modular& m) { v = int((long long)v*m.v%_MOD); return *this; }
    Modular& operator/=(const Modular& m) { return (*this) *= inv(m); }
    Modular operator-() const { return Modular(-v); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    friend Modular pow(Modular a, long long p) {
        Modular ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans; 
    }
    friend Modular inv(const Modular& a) { assert(a.v != 0); return pow(a,_MOD-2); }

    friend Modular operator+(Modular a, const Modular& b) { return a += b; }
    friend Modular operator-(Modular a, const Modular& b) { return a -= b; }
    friend Modular operator*(Modular a, const Modular& b) { return a *= b; }
    friend Modular operator/(Modular a, const Modular& b) { return a /= b; }
    friend Modular operator++(Modular& a, int) { Modular r = a; ++a; return r; }
    friend Modular operator--(Modular& a, int) { Modular r = a; --a; return r; }
};

int main() {
    
}