#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree2D {
private:
    int n, m;
    vector<vector<T>> arr;
    vector<vector<T>> segTree;

    T combine(T left, T right) {
        return left + right;  // Change this
    }

    void buildY(int nodeX, int startX, int endX, int nodeY, int startY, int endY) {
        if (startY == endY) {
            if (startX == endX)
                segTree[nodeX][nodeY] = arr[startX][startY];
            else
                segTree[nodeX][nodeY] = combine(segTree[2 * nodeX + 1][nodeY], segTree[2 * nodeX + 2][nodeY]);
        } else {
            int midY = (startY + endY) / 2;
            buildY(nodeX, startX, endX, 2 * nodeY + 1, startY, midY);
            buildY(nodeX, startX, endX, 2 * nodeY + 2, midY + 1, endY);
            segTree[nodeX][nodeY] = combine(segTree[nodeX][2 * nodeY + 1], segTree[nodeX][2 * nodeY + 2]);
        }
    }

    void buildX(int nodeX, int startX, int endX) {
        if (startX != endX) {
            int midX = (startX + endX) / 2;
            buildX(2 * nodeX + 1, startX, midX);
            buildX(2 * nodeX + 2, midX + 1, endX);
        }
        buildY(nodeX, startX, endX, 0, 0, m - 1);
    }

    T queryY(int idxY, int startY, int endY, int lY, int rY, int nodeX) {
        if (lY == startY && rY == endY)
            return segTree[nodeX][idxY];
        int midY = (startY + endY) / 2;
        if (rY <= midY)
            return queryY(2 * idxY + 1, startY, midY, lY, rY, nodeX);
        else if (lY > midY)
            return queryY(2 * idxY + 2, midY + 1, endY, lY, rY, nodeX);
        else
            return combine(
                queryY(2 * idxY + 1, startY, midY, lY, midY, nodeX),
                queryY(2 * idxY + 2, midY + 1, endY, midY + 1, rY, nodeX)
            );
    }

    T queryX(int idxX, int startX, int endX, int lX, int rX, int lY, int rY) {
        if (lX == startX && rX == endX)
            return queryY(0, 0, m - 1, lY, rY, idxX);
        int midX = (startX + endX) / 2;
        if (rX <= midX)
            return queryX(2 * idxX + 1, startX, midX, lX, rX, lY, rY);
        else if (lX > midX)
            return queryX(2 * idxX + 2, midX + 1, endX, lX, rX, lY, rY);
        else
            return combine(
                queryX(2 * idxX + 1, startX, midX, lX, midX, lY, rY),
                queryX(2 * idxX + 2, midX + 1, endX, midX + 1, rX, lY, rY)
            );
    }

    void updateY(int nodeX, int startX, int endX, int nodeY, int startY, int endY, int y, T value) {
        if (startY == endY) {
            if (startX == endX)
                segTree[nodeX][nodeY] = value;
            else
                segTree[nodeX][nodeY] = combine(segTree[2 * nodeX + 1][nodeY], segTree[2 * nodeX + 2][nodeY]);
        } else {
            int midY = (startY + endY) / 2;
            if (y <= midY)
                updateY(nodeX, startX, endX, 2 * nodeY + 1, startY, midY, y, value);
            else
                updateY(nodeX, startX, endX, 2 * nodeY + 2, midY + 1, endY, y, value);
            segTree[nodeX][nodeY] = combine(segTree[nodeX][2 * nodeY + 1], segTree[nodeX][2 * nodeY + 2]);
        }
    }

    void updateX(int nodeX, int startX, int endX, int x, int y, T value) {
        if (startX != endX) {
            int midX = (startX + endX) / 2;
            if (x <= midX)
                updateX(2 * nodeX + 1, startX, midX, x, y, value);
            else
                updateX(2 * nodeX + 2, midX + 1, endX, x, y, value);
        }
        updateY(nodeX, startX, endX, 0, 0, m - 1, y, value);
    }

public:
    SegmentTree2D(const vector<vector<T>>& input) {
        n = input.size();
        m = input[0].size();
        arr = input;
        segTree.resize(4 * n, vector<T>(4 * m));
        buildX(0, 0, n - 1);
    }

    T query(int x1, int y1, int x2, int y2) {
        return queryX(0, 0, n - 1, x1, x2, y1, y2);
    }

    void update(int x, int y, T value) {
        arr[x][y] = value;
        updateX(0, 0, n - 1, x, y, value);
    }
}; // * Note: 0-based index

int main() {
    
}