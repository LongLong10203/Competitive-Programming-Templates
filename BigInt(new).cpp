#include <bits/stdc++.h>
using namespace std;

class BigInt {
private:
    string number;

    void normalize() {
        if(number.size() > 1) {
            bool neg = (number[0] == '-');
            int start = neg ? 1 : 0;
            while(number.size() > start + 1 && number[start] == '0') number.erase(start, 1);
            if(number == "-") number = "0";
        }
    }

    static void fft(vector<complex<double>> &a, bool invert) {
        int n = (int)a.size();
        for(int i = 1, j = 0; i < n; i++){
            int bit = n >> 1;
            for(; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if(i < j) swap(a[i], a[j]);
        }
        for(int len = 2; len <= n; len <<= 1){
            double ang = 2*acos(-1)/len * (invert ? -1 : 1);
            complex<double> wlen(cos(ang), sin(ang));
            for(int i = 0; i < n; i += len){
                complex<double> w(1);
                for(int j = 0; j < len/2; j++){
                    complex<double> u = a[i+j], v = a[i+j+len/2]*w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }
        if(invert){
            for(auto &x : a) x /= n;
        }
    }

    static string multiplyFFT(const string &num1, const string &num2) {
        bool neg = false;
        int start1 = 0, start2 = 0;
        if(num1[0] == '-') { neg = !neg; start1 = 1; }
        if(num2[0] == '-') { neg = !neg; start2 = 1; }

        vector<int> a, b;
        for(int i = (int)num1.size()-1; i >= start1; i--) a.push_back(num1[i]-'0');
        for(int i = (int)num2.size()-1; i >= start2; i--) b.push_back(num2[i]-'0');

        int n = 1;
        while(n < (int)(a.size() + b.size())) n <<= 1;
        vector<complex<double>> fa(n), fb(n);
        for(size_t i = 0; i < a.size(); i++) fa[i] = a[i];
        for(size_t i = 0; i < b.size(); i++) fb[i] = b[i];

        fft(fa, false); fft(fb, false);
        for(int i = 0; i < n; i++) fa[i] *= fb[i];
        fft(fa, true);

        vector<int> result(n);
        for(int i = 0; i < n; i++){
            long long val = (long long)llround(fa[i].real());
            if(val < 0) val = 0;
            result[i] = (int)val;
        }
        for(int i = 0; i < n-1; i++){
            result[i+1] += result[i]/10;
            result[i] %= 10;
        }
        while(result.size()>1 && result.back()==0) result.pop_back();

        string ans;
        if(neg && !(result.size()==1 && result[0] == 0)) ans.push_back('-');
        for(int i = (int)result.size()-1; i >= 0; i--) ans.push_back((char)(result[i]+'0'));
        return ans;
    }

    static string addStrings(const string &a, const string &b) {
        string res;
        int carry = 0, i = (int)a.size() - 1, j = (int)b.size() - 1;
        while(i >= 0 || j >= 0 || carry) {
            int x = (i >= 0 ? a[i--] - '0' : 0);
            int y = (j >= 0 ? b[j--] - '0' : 0);
            int sum = x + y + carry;
            carry = sum / 10; sum %= 10;
            res.push_back((char)('0' + sum));
        }
        reverse(res.begin(), res.end());
        return res;
    }

    static string subStrings(const string &a, const string &b) {
        string res;
        int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
        while(i >= 0) {
            int x = a[i--] - '0' - carry;
            int y = (j >= 0 ? b[j--] - '0' : 0);
            if(x < y) { x += 10; carry = 1; } else carry = 0;
            res.push_back((char)('0' + (x - y)));
        }
        while(res.size() > 1 && res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return res;
    }

public:
    BigInt() : number("0") {}
    BigInt(const string &s) : number(s.empty() ? "0" : s) { normalize(); }
    BigInt(long long v) { number = to_string(v); normalize(); }
    BigInt(int v) { number = to_string(v); normalize(); }

    BigInt& operator=(const string &s) { number = s; normalize(); return *this; }
    BigInt& operator=(long long v) { number = to_string(v); normalize(); return *this; }
    BigInt& operator=(int v) { number = to_string(v); normalize(); return *this; }

    bool operator==(const BigInt &other) const { return number == other.number; }
    bool operator!=(const BigInt &other) const { return !(*this == other); }
    bool operator<(const BigInt &other) const {
        if(number[0] == '-' && other.number[0] != '-') return true;
        if(number[0] != '-' && other.number[0] == '-') return false;

        bool neg = (number[0] == '-');
        string a = neg ? number.substr(1) : number;
        string b = neg ? other.number.substr(1) : other.number;

        if(a.size() != b.size()) {
            return (a.size() < b.size()) ^ neg;
        }
        return (a < b) ^ neg;
    }
    bool operator>(const BigInt &other) const { return other < *this; }
    bool operator<=(const BigInt &other) const { return !(other < *this); }
    bool operator>=(const BigInt &other) const { return !(*this < other); }

    template <typename T>
    bool operator==(T other) const { return *this == BigInt(other); }
    template <typename T>
    bool operator!=(T other) const { return !(*this == other); }
    template <typename T>
    bool operator<(T other) const { return *this < BigInt(other); }
    template <typename T>
    bool operator>(T other) const { return other < *this; }
    template <typename T>
    bool operator<=(T other) const { return !(other < *this); }
    template <typename T>
    bool operator>=(T other) const { return !(*this < other); }

    template <typename T>
    friend bool operator==(T lhs, const BigInt &rhs) { return BigInt(lhs) == rhs; }
    template <typename T>
    friend bool operator!=(T lhs, const BigInt &rhs) { return BigInt(lhs) != rhs; }
    template <typename T>
    friend bool operator<(T lhs, const BigInt &rhs) { return BigInt(lhs) < rhs; }
    template <typename T>
    friend bool operator>(T lhs, const BigInt &rhs) { return rhs < lhs; }
    template <typename T>
    friend bool operator<=(T lhs, const BigInt &rhs) { return !(rhs < lhs); }
    template <typename T>
    friend bool operator>=(T lhs, const BigInt &rhs) { return !(lhs < rhs); }

    BigInt operator-() const {
        BigInt r = *this;
        if(r.number != "0") {
            if(r.number[0] == '-') r.number.erase(0, 1);
            else r.number.insert(r.number.begin(), '-');
        }
        return r;
    }

    BigInt operator+(const BigInt &other) const {
        if(number[0] == '-' && other.number[0] == '-') {
            return -BigInt(addStrings(number.substr(1), other.number.substr(1)));
        } else if(number[0] == '-') {
            return BigInt(other) - BigInt(number.substr(1));
        } else if(other.number[0] == '-') {
            return *this - BigInt(other.number.substr(1));
        }
        return BigInt(addStrings(number, other.number));
    }

    BigInt operator-(const BigInt &other) const {
        if(other.number[0] == '-') {
            return *this + BigInt(other.number.substr(1));
        } else if(number[0] == '-') {
            return -BigInt(addStrings(number.substr(1), other.number));
        }
        if(*this < other) {
            return -BigInt(subStrings(other.number, number));
        } else {
            return BigInt(subStrings(number, other.number));
        }
    }

    BigInt operator*(const BigInt &other) const {
        return BigInt(multiplyFFT(number, other.number));
    }

    BigInt& operator+=(const BigInt &other) { *this = *this + other; return *this; }
    BigInt& operator-=(const BigInt &other) { *this = *this - other; return *this; }
    BigInt& operator*=(const BigInt &other) { *this = *this * other; return *this; }

    BigInt& operator++() { *this += 1; return *this; }
    BigInt operator++(int) { BigInt tmp = *this; ++(*this); return tmp; }
    BigInt& operator--() { *this -= 1; return *this; }
    BigInt operator--(int) { BigInt tmp = *this; --(*this); return tmp; }

    friend ostream& operator<<(ostream &out, const BigInt &val) {
        out << val.number; 
        return out;
    }

    friend istream& operator>>(istream &in, BigInt &val) {
        in >> val.number;
        val.normalize();
        return in;
    }

    friend BigInt abs(const BigInt &val) {
        if(val.number[0] == '-') return BigInt(val.number.substr(1));
        return val;
    }

    friend BigInt pow(const BigInt &base, int exp, const BigInt &mod = BigInt("0")) {
        BigInt result = 1;
        BigInt b = base;
        while(exp > 0) {
            if(exp % 2 == 1) {
                result *= b;
                if(mod != BigInt("0")) result %= mod;
            }
            b *= b;
            if(mod != BigInt("0")) b %= mod;
            exp /= 2;
        }
        return result;
    }

    friend BigInt gcd(const BigInt &a, const BigInt &b) {
        BigInt x = a, y = b;
        while(y != 0) {
            BigInt temp = y;
            y = x % y;
            x = temp;
        }
        return x;
    }

    BigInt operator%(const BigInt &other) const {
        BigInt divd = abs(*this);
        BigInt divs = abs(other);
        BigInt rem = 0;

        for (size_t i = 0; i < divd.number.size(); ++i) {
            rem = rem * 10 + (divd.number[i] - '0');
            while (rem >= divs) {
                rem -= divs;
            }
        }

        if (this->number[0] == '-') rem = -rem;
        return rem;
    }

    BigInt& operator%=(const BigInt &other) {
        *this = *this % other;
        return *this;
    }

    int toInt() const {
        return stoi(number);
    }

    long long toLL() const {
        return stoll(number);
    }

    string toString() const {
        return number;
    }
};

int main() {
    
}