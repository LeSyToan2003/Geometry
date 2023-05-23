#include <bits/stdc++.h>

using namespace std;

vector <int> vecA;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    vecA.resize(3);
    cin >> vecA[0] >> vecA[1] >> vecA[2];
    sort(vecA.begin(), vecA.end());
    cout << max(vecA[2] + 1 - vecA[0] - vecA[1], 0);
}

int main() {
    Task();
    Solve();
}

