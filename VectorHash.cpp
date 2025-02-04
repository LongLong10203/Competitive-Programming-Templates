#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct VectorHash {
    size_t operator()(const vector<T>& v) const {
        size_t res = 0;
        for (const auto& elem : v) {
            res ^= hash<T>()(elem) + 0x9e3779b97f4a7c15ULL + (res << 6) + (res >> 2);
        }
        return res;
    }
};

int main() {
    
}