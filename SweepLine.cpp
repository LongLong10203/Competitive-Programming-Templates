#include <bits/stdc++.h>
using namespace std;

template<typename T>
istream& operator>>(istream& is, vector<T>& v) { for (auto& x : v) is >> x; return is; }

template<typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) { return is >> p.first >> p.second; }

template<typename T, size_t N>
istream& operator>>(istream& is, array<T, N>& a) { for (auto& x : a) is >> x; return is; }

template<typename... T>
istream& operator>>(istream& is, tuple<T...>& t) { apply([&](auto&&... args) { ((is >> args), ...); }, t); return is; }

template <typename T1, typename T2>
struct Event {
    T1 l, r;
    T2 cnt;
};

template <typename T1, typename T2>
class SweepLine { // experimental
public:
    SweepLine() : cnt(T2(0)) {}

    void add(T1 start, T1 end, T2 inc=1) {
        events[start] += inc;
        events[end] -= inc;
    }

    vector<Event<T1, T2>> cal() {
        vector<Event<T1, T2>> result;
        T1 start = -1;

        for (auto &[pos, diff] : events) {
            T2 prev_cnt = cnt;
            cnt += diff;

            if (prev_cnt == 0 && cnt > 0) {
                start = pos;
            }

            if (prev_cnt > 0 && cnt == 0) {
                result.push_back({start, pos, prev_cnt});
                start = -1;
            }

            if (prev_cnt > 0 && cnt > 0 && start != pos) {
                result.push_back({start, pos, prev_cnt});
                start = pos;
            }
        }
        return result;
    }

private:
    map<T1, T2> events;
    T2 cnt;
};

int main() {
    
}