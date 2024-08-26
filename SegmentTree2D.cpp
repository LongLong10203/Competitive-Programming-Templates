#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree2D {
private:
    vector<vector<T>> tree, data;
    int n, m;

    T combine(T a, T b) {
        return a + b; // modify this
    }

    void build_y(int x, int lx, int rx, int y, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx)
                tree[x][y] = data[lx][ly];
            else
                tree[x][y] = combine(tree[2*x][y], tree[2*x+1][y]);
        } else {
            int my = (ly + ry) / 2;
            build_y(x, lx, rx, 2*y, ly, my);
            build_y(x, lx, rx, 2*y+1, my+1, ry);
            tree[x][y] = combine(tree[x][2*y], tree[x][2*y+1]);
        }
    }

    void build_x(int x, int lx, int rx) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(2*x, lx, mx);
            build_x(2*x+1, mx+1, rx);
        }
        build_y(x, lx, rx, 1, 0, m-1);
    }

    T query_y(int x, int y, int ly, int ry, int qly, int qry) {
        if (qly == ly && qry == ry)
            return tree[x][y];
        int my = (ly + ry) / 2;
        if (qry <= my)
            return query_y(x, 2*y, ly, my, qly, qry);
        else if (qly > my)
            return query_y(x, 2*y+1, my+1, ry, qly, qry);
        else
            return combine(
                query_y(x, 2*y, ly, my, qly, my),
                query_y(x, 2*y+1, my+1, ry, my+1, qry)
            );
    }

    T query_x(int x, int lx, int rx, int qlx, int qrx, int qly, int qry) {
        if (qlx == lx && qrx == rx)
            return query_y(x, 1, 0, m-1, qly, qry);
        int mx = (lx + rx) / 2;
        if (qrx <= mx)
            return query_x(2*x, lx, mx, qlx, qrx, qly, qry);
        else if (qlx > mx)
            return query_x(2*x+1, mx+1, rx, qlx, qrx, qly, qry);
        else {
            return combine(
                query_x(2*x, lx, mx, qlx, mx, qly, qry),
                query_x(2*x+1, mx+1, rx, mx+1, qrx, qly, qry)
            );
        }
    }

    void update_y(int x, int lx, int rx, int y, int ly, int ry, int uy, T val) {
        if (ly == ry) {
            if (lx == rx)
                tree[x][y] = val;
            else
                tree[x][y] = combine(tree[2*x][y], tree[2*x+1][y]);
        } else {
            int my = (ly + ry) / 2;
            if (uy <= my)
                update_y(x, lx, rx, 2*y, ly, my, uy, val);
            else
                update_y(x, lx, rx, 2*y+1, my+1, ry, uy, val);
            tree[x][y] = combine(tree[x][2*y], tree[x][2*y+1]);
        }
    }

    void update_x(int x, int lx, int rx, int ux, int uy, T val) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (ux <= mx)
                update_x(2*x, lx, mx, ux, uy, val);
            else
                update_x(2*x+1, mx+1, rx, ux, uy, val);
        }
        update_y(x, lx, rx, 1, 0, m-1, uy, val);
    }

public:
    SegmentTree2D(const vector<vector<T>>& input_data) {
        data = input_data;
        n = data.size();
        m = data[0].size();
        tree.resize(4 * n, vector<T>(4 * m));
        build_x(1, 0, n-1);
    }

    T query(int qlx, int qrx, int qly, int qry) {
        return query_x(1, 0, n-1, qlx, qrx, qly, qry);
    }

    void update(int ux, int uy, T val) {
        update_x(1, 0, n-1, ux, uy, val);
    }
}; // * Note: 0-based index

int main() {
    
}