#include <bits/stdc++.h>
using namespace std;

template <typename T>
class PrefixSum2D {
    vector<vector<T>> arr;
    size_t rows, cols;

    void build() {
        for (size_t i = 0; i < rows; ++i)
            partial_sum(arr[i].begin(), arr[i].end(), arr[i].begin());
        for (size_t j = 0; j < cols; ++j)
            for (size_t i = 1; i < rows; ++i)
                arr[i][j] += arr[i - 1][j];
    }

public:
    PrefixSum2D() : rows(0), cols(0) {}
    PrefixSum2D(size_t r, size_t c) : rows(r), cols(c), arr(r, vector<T>(c)) {}
    PrefixSum2D(const vector<vector<T>>& v) : arr(v), rows(v.size()), cols(v[0].size()) {
        build();
    }

    const vector<vector<T>>& get() const {
        return arr;
    }

    T query(size_t r1, size_t c1, size_t r2, size_t c2) const {
        return arr[r2][c2] - (r1 ? arr[r1 - 1][c2] : 0) - (c1 ? arr[r2][c1 - 1] : 0) + (r1 && c1 ? arr[r1 - 1][c1 - 1] : 0);
    }

    friend ostream& operator<<(ostream& os, const PrefixSum2D& ps) {
        for (size_t i = 0; i < ps.arr.size(); i++) {
            for (size_t j = 0; j < ps.arr[i].size(); j++) {
                os << ps.arr[i][j];
                if (j + 1 < ps.arr[i].size()) os << ' ';
            }
            if (i + 1 < ps.arr.size()) os << '\n';
        }
        return os;
    }

    friend istream& operator>>(istream& is, PrefixSum2D& ps) {
        for (auto& row : ps.arr)
            for (auto& x : row)
                is >> x;
        ps.build();
        return is;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    
}