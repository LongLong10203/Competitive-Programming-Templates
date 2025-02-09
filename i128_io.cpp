#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;

istream& operator>>(istream& in, i128& num) {
    string s;
    in >> s;
    num = 0;
    bool neg = false;
    for (char c : s) {
        if (c == '-') {
            neg = true;
        } else {
            num = num * 10 + (c - '0');
        }
    }
    if (neg) {
        num = -num;
    }
    return in;
}

ostream& operator<<(ostream& out, const i128& num) {
    if (num == 0) {
        out << '0';
        return out;
    }
    i128 temp = num;
    if (temp < 0) {
        out << '-';
        temp = -temp;
    }
    string s;
    while (temp > 0) {
        s += '0' + (temp % 10);
        temp /= 10;
    }
    reverse(s.begin(), s.end());
    out << s;
    return out;
}

int main() {
    
}