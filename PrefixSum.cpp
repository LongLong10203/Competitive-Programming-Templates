#include <bits/stdc++.h>
using namespace std;

template <typename T>
class PrefixSum {
    vector<T> arr;

    void build() {
        partial_sum(arr.begin(), arr.end(), arr.begin());
    }

public:
    PrefixSum() {}
    PrefixSum(size_t n) {
        arr.resize(n);
    }
    PrefixSum(const vector<T>& v) : arr(v) {
        build();
    }

    vector<T> operator()() {
        return arr;
    }

    T query(size_t l, size_t r) const {
        return (l == 0) ? arr[r] : arr[r] - arr[l - 1];
    }

    friend ostream& operator<<(ostream& os, const PrefixSum& ps) {
        for (auto x : ps.arr)
            os << x << ' ';
        return os;
    }

    friend istream& operator>>(istream& is, PrefixSum& ps) {
        for (auto &x : ps.arr)
            is >> x;
        ps.build();
        return is;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    
}