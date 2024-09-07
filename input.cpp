#include <bits/stdc++.h>
using namespace std;

template<typename T>
istream& operator>>(istream& is, vector<T>& v) { for (auto& x : v) is >> x; return is; }

template<typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) { return is >> p.first >> p.second; }

template<typename T, size_t N>
istream& operator>>(istream& is, array<T, N>& a) { for (auto& x : a) is >> x; return is; }

template<typename... T>
istream& operator>>(istream& is, tuple<T...>& t) { apply([&](auto&&... args) { ((is >> args), ...); }, t); return is; }

int main() {
    
}