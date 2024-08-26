#include <bits/stdc++.h>
using namespace std;

template<typename T>
class SparseTable {
    vector<vector<T>> table;
    vector<int> log;

    T combine(T left, T right) {
        return max(left, right); // modify this
    }

public:
    SparseTable(const vector<T>& data) {
        int n = data.size();
        int maxLog = 32 - __builtin_clz(n);
        table.resize(n, vector<T>(maxLog));
        log.resize(n + 1);

        log[1] = 0;
        for (int i = 2; i <= n; i++)
            log[i] = log[i / 2] + 1;

        for (int i = 0; i < n; i++)
            table[i][0] = data[i];

        for (int j = 1; j < maxLog; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[i][j] = combine(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    T query(int left, int right) {
        int j = log[right - left + 1];
        return combine(table[left][j], table[right - (1 << j) + 1][j]);
    }
}; // * Note: 0-based index

int main() {
    
}