#include <bits/stdc++.h>
using namespace std;
 
template <typename T1, typename T2>
struct Event {
    T1 l, r;
    T2 cnt;
};
 
template <typename T1, typename T2>
class SweepLine {
public:
    SweepLine() : cnt(T2(0)) {}

    void add(T1 start, T1 end, T2 inc=1) {
        events[start] += inc;
        events[end + 1] -= inc;
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

typedef long long ll;

int main() {
    
}