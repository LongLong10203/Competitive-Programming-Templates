#include <bits/stdc++.h>
using namespace std;

// vector I/O
template <class T> istream& operator>>(istream& is, vector<T>& v) {
    for (auto it=v.begin();it!=v.end();++it) cin >> *it;
    return is;
}
template <class T> ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it = v.begin();it != v.end(); it++) cout << *it << ' ';
    return os;
}

