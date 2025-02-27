#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;

ostream& operator<<(ostream& os, const i128 &n) {
    if (n == 0)
        return os << '0';
    i128 t = n;
    if (t < 0) {
        os << "-";
        t = -t;
    }
    string s;
    while (t) {
        s.push_back('0' + (t % 10));
        t /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

istream& operator>>(istream& is, i128 &n) {
    string s;
    is >> s;
    n = 0;
    bool neg = s[0] == '-';
    for (size_t i = neg ? 1 : 0; i < s.size(); ++i)
        n = n * 10 + (s[i] - '0');
    if (neg)
        n = -n;
    return is;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);


}