#include <bits/stdc++.h>
using namespace std;

template <typename T>
class DifferenceArray2D {
    vector<vector<T>> arr;
public:
    DifferenceArray2D() {}
    DifferenceArray2D(size_t rows, size_t cols) : arr(rows, vector<T>(cols, 0)) {}

    void increment(size_t r1, size_t c1, size_t r2, size_t c2, T val) {
        arr[r1][c1] += val;
        if (r2 + 1 < arr.size()) arr[r2 + 1][c1] -= val;
        if (c2 + 1 < arr[0].size()) arr[r1][c2 + 1] -= val;
        if (r2 + 1 < arr.size() && c2 + 1 < arr[0].size()) arr[r2 + 1][c2 + 1] += val;
    }

    void build() {
        for (auto& row : arr)
            partial_sum(row.begin(), row.end(), row.begin());
        for (size_t j = 0; j < arr[0].size(); ++j)
            for (size_t i = 1; i < arr.size(); ++i)
                arr[i][j] += arr[i - 1][j];
    }
    
    const vector<vector<T>>& get() const {
        return arr;
    }

    friend ostream& operator<<(ostream& os, const DifferenceArray2D& da) {
        for (size_t i = 0; i < da.arr.size(); ++i) {
            for (size_t j = 0; j < da.arr[i].size(); ++j) {
                os << da.arr[i][j];
                if (j + 1 < da.arr[i].size()) os << ' ';
            }
            if (i + 1 < da.arr.size()) os << '\n';
        }
        return os;
    }

    friend istream& operator>>(istream& is, DifferenceArray2D& da) {
        for (auto &row : da.arr)
            for (auto &x : row)
                is >> x;
        return is;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    
}