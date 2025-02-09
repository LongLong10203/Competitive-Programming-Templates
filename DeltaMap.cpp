#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U>
class DeltaMap { // experimental
private:
    map<T, U> diff;
public:
    void increment(T l, T r, U val) {
        diff[l] += val;
        diff[r + 1] -= val;
    }

    T countEqual(U target) {
        U cur = 0;
        T count = 0;
        auto it = diff.begin();
        T prev_idx = it->first;
        for (auto &[idx, val] : diff) {
            if (cur == target) {
                count += (idx - prev_idx);
            }
            cur += val;
            prev_idx = idx;
        }
        return count;
    }

    T countMore(U target) {
        U cur = 0;
        T count = 0;
        auto it = diff.begin();
        T prev_idx = it->first;
        for (auto &[idx, val] : diff) {
            if (cur > target)
                count += (idx - prev_idx);
            cur += val;
            prev_idx = idx;
        }
        return count;
    }

    T countLess(U target) {
        U cur = 0;
        T count = 0;
        auto it = diff.begin();
        T prev_idx = it->first;
        for (auto &[idx, val] : diff) {
            if (cur < target)
                count += (idx - prev_idx);
            cur += val;
            prev_idx = idx;
        }
        return count;
    }

    U getValueAt(T pos) {
        U cur = 0;
        for (auto it = diff.begin(); it != diff.end() && it->first <= pos; ++it) {
            cur += it->second;
        }
        return cur;
    }

    void setValueAt(T pos, U newVal) {
        U current = getValueAt(pos);
        U diffVal = newVal - current;
        increment(pos, pos, diffVal);
    }

    void reset() {
        diff.clear();
    }

    vector<tuple<T, T, U>> getSegments(T L, T R) {
        vector<tuple<T, T, U>> segments;
        U cur = getValueAt(L);
        T start = L;
        auto it = diff.lower_bound(L);
        while (it != diff.end() && it->first <= R) {
            T boundary = it->first;
            if (boundary > start) {
                segments.push_back(make_tuple(start, boundary - 1, cur));
            }
            cur += it->second;
            start = boundary;
            ++it;
        }
        if (start <= R) {
            segments.push_back(make_tuple(start, R, cur));
        }
        return segments;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    
}