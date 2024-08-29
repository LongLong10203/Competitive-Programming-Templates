#include <bits/stdc++.h>
using namespace std;

class i128 {
private:
    __int128 value;

public:
    i128() : value(0) {}
    i128(__int128 v) : value(v) {}

    friend istream& operator>>(istream& in, i128& num) {
        string input;
        in >> input;
        __int128 result = 0;
        bool negative = false;
        size_t i = 0;
        if (input[0] == '-') {
            negative = true;
            i = 1;
        }
        for (; i < input.size(); ++i)
            result = result * 10 + (input[i] - '0');
        num.value = negative ? -result : result;
        return in;
    }

    friend ostream& operator<<(ostream& out, const i128& num) {
        if (num.value < 0)
            out << '-';
        __int128 temp = num.value < 0 ? -num.value : num.value;
        string str;
        do {
            str += '0' + temp % 10;
            temp /= 10;
        } while (temp != 0);
        reverse(str.begin(), str.end());
        out << str;
        return out;
    }

    bool operator>(const i128& other) const {
        return value > other.value;
    }

    bool operator<(const i128& other) const {
        return value < other.value;
    }
};

int main() {
    
}