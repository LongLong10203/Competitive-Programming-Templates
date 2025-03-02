#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Catalan {
    vector<T> cat;
    Catalan(int n) : cat(n + 1) {
        cat[0] = 1;
        for (int i = 1; i <= n; i++)
            cat[i] = cat[i - 1] * (4 * i - 2) / (i + 1);
    }
    T operator[](int i) const { return cat[i]; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    
}