#include <bits/stdc++.h>
using namespace std;

template <typename T>
class PrefixSum {
private:
    vector<T> prefix;

public:
    PrefixSum(const vector<T>& data) {
        prefix.resize(data.size()+1, 0);
        for (size_t i = 0; i < data.size(); ++i)
            prefix[i + 1] = prefix[i] + data[i];
    }

    T query(int l, int r) const {
        return prefix[r + 1] - prefix[l];
    }
};

int main() {
    
}