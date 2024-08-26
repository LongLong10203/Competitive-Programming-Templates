#include <bits/stdc++.h>
using namespace std;

template <typename T>
class PrefixSum2D {
private:
    vector<vector<T>> prefix;

public:
    PrefixSum2D(const vector<vector<T>>& data) {
        int rows = data.size();
        int cols = data[0].size();
        prefix.resize(rows+1, vector<T>(cols+1, 0));
        for (int i = 1; i <= rows; ++i)
            for (int j = 1; j <= cols; ++j)
                prefix[i][j] = data[i-1][j-1] 
                             + prefix[i-1][j] 
                             + prefix[i][j-1] 
                             - prefix[i-1][j-1];
    }

    T query(int r1, int c1, int r2, int c2) const {
        return prefix[r2+1][c2+1] 
               - prefix[r1][c2+1] 
               - prefix[r2+1][c1] 
               + prefix[r1][c1];
    }
};

int main() {

}