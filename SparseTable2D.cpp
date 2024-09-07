#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SparseTable2D {
public:
    SparseTable2D(const vector<vector<T>>& matrix) 
        : n(matrix.size()), m(matrix[0].size()) {
        build(matrix);
    }

    T query(int x1, int y1, int x2, int y2) {
        int kx = log2(x2 - x1 + 1);
        int ky = log2(y2 - y1 + 1);
        
        T res1 = combine(st[kx][ky][x1][y1], st[kx][ky][x1][y2 - (1 << ky) + 1]);
        T res2 = combine(st[kx][ky][x2 - (1 << kx) + 1][y1], st[kx][ky][x2 - (1 << kx) + 1][y2 - (1 << ky) + 1]);

        return combine(res1, res2);
    }

private:
    int n, m;
    vector<vector<vector<vector<T>>>> st;

    void build(const vector<vector<T>>& matrix) {
        int maxLogX = log2(n) + 1;
        int maxLogY = log2(m) + 1;

        st.resize(maxLogX, vector<vector<vector<T>>>(maxLogY, vector<vector<T>>(n, vector<T>(m))));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                st[0][0][i][j] = matrix[i][j];
            }
        }

        for (int kx = 0; (1 << kx) <= n; ++kx) {
            for (int ky = 0; (1 << ky) <= m; ++ky) {
                if (kx == 0 && ky == 0) continue;
                
                for (int i = 0; i + (1 << kx) <= n; ++i) {
                    for (int j = 0; j + (1 << ky) <= m; ++j) {
                        if (kx == 0) {
                            st[kx][ky][i][j] = combine(st[kx][ky - 1][i][j], st[kx][ky - 1][i][j + (1 << (ky - 1))]);
                        } else if (ky == 0) {
                            st[kx][ky][i][j] = combine(st[kx - 1][ky][i][j], st[kx - 1][ky][i + (1 << (kx - 1))][j]);
                        } else {
                            T res1 = combine(st[kx - 1][ky - 1][i][j], st[kx - 1][ky - 1][i + (1 << (kx - 1))][j]);
                            T res2 = combine(st[kx - 1][ky - 1][i][j + (1 << (ky - 1))], st[kx - 1][ky - 1][i + (1 << (kx - 1))][j + (1 << (ky - 1))]);
                            st[kx][ky][i][j] = combine(res1, res2);
                        }
                    }
                }
            }
        }
    }

    // * Note: range sum query NOT supported
    T combine(T left, T right) {
        return min(left, right); // modify this
    }
}; // * Note: 0-based index

int main() {
    
}