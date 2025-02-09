#include <bits/stdc++.h>
using namespace std;

template <typename T>
class DifferenceArray {
    vector<T> arr;
public:
    DifferenceArray() {}
    DifferenceArray(size_t n) : arr(n) {}

    void increment(size_t l, size_t r, T val) {
        arr[l] += val;
        if (r + 1 < arr.size())
            arr[r + 1] -= val;
    }

    void build() {
        partial_sum(arr.begin(), arr.end(), arr.begin());
    }
    
    const vector<T>& get() const {
        return arr;
    }

    friend ostream& operator<<(ostream& os, const DifferenceArray& da) {
        for (auto x : da.arr)
            os << x << ' ';
        return os;
    }

    friend istream& operator>>(istream& is, DifferenceArray& da) {
        for (auto &x : da.arr)
            is >> x;
        return is;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    
}