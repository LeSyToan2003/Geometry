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
    vecA.resize(4);
    for (int i = 0; i < 4; ++i) {
        cin >> vecA[i];
    }
    sort(vecA.begin(), vecA.end());
    bool chk = false;
    for (int i = 0; i + 2 < 4; ++i) {
        for (int j = i + 1; j + 1 < 4; ++j) {
            for (int k = j + 1; k < 4; ++k) {
                if (vecA[i] + vecA[j] > vecA[k]) {
                    return void(cout << "TRIANGLE");
                } else if (vecA[i] + vecA[j] == vecA[k]) {
                    chk = true;
                }
            }
        }
    }
    cout << (chk ? "SEGMENT" : "IMPOSSIBLE");
}

int main() {
    Task();
    Solve();
}
