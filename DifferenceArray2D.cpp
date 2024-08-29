#include <bits/stdc++.h>
using namespace std;

template<typename T>
class DifferenceArray2D {
    vector<vector<T>> diff;

public:
    DifferenceArray2D(const vector<vector<T>>& arr) {
        int n = arr.size(), m = arr[0].size();
        diff.resize(n + 1, vector<T>(m + 1, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                diff[i][j] = arr[i][j];
                if (i > 0) diff[i][j] -= arr[i - 1][j];
                if (j > 0) diff[i][j] -= arr[i][j - 1];
                if (i > 0 && j > 0) diff[i][j] += arr[i - 1][j - 1];
            }
        }
    }

    void increment(int x1, int y1, int x2, int y2, T value) {
        diff[x1][y1] += value;
        if (x2 + 1 < diff.size()) diff[x2 + 1][y1] -= value;
        if (y2 + 1 < diff[0].size()) diff[x1][y2 + 1] -= value;
        if (x2 + 1 < diff.size() && y2 + 1 < diff[0].size()) diff[x2 + 1][y2 + 1] += value;
    }

    vector<vector<T>> get() const {
        int n = diff.size() - 1, m = diff[0].size() - 1;
        vector<vector<T>> res(n, vector<T>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i][j] = diff[i][j];
                if (i > 0) res[i][j] += res[i - 1][j];
                if (j > 0) res[i][j] += res[i][j - 1];
                if (i > 0 && j > 0) res[i][j] -= res[i - 1][j - 1];
            }
        }
        return res;
    }
};

int main() {
    
}