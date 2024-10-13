#include <bits/stdc++.h>
using namespace std;

vector<int> tot(int n) {
    vector<int> phi(n + 1);
    for (int i = 1; i <= n; i++)
        phi[i] = i;
    for (int p = 2; p <= n; p++)
        if (phi[p] == p)
            for (int k = p; k <= n; k += p)
                phi[k] -= phi[k] / p;
    return phi;
}

int main() {

}