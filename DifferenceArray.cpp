#include <bits/stdc++.h>
using namespace std;

template<typename T>
class DifferenceArray {
    vector<T> diff;

public:
    DifferenceArray(const vector<T>& arr) {
        int n = arr.size();
        diff.resize(n + 1, 0);
        diff[0] = arr[0];
        for (int i = 1; i < n; i++)
            diff[i] = arr[i] - arr[i - 1];
    }

    void increment(int l, int r, T value) {
        diff[l] += value;
        if (r + 1 < diff.size()) {
            diff[r + 1] -= value;
        }
    }

    vector<T> get() const {
        vector<T> result(diff.size() - 1);
        result[0] = diff[0];
        for (int i = 1; i < result.size(); i++)
            result[i] = result[i - 1] + diff[i];
        return result;
    }
}; // * Note: 0-based index

int main() {
    
}