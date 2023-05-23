#include <bits/stdc++.h>

using namespace std;

int T, n;
vector <int> vecA;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        vecA.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> vecA[i];
        }
        if (vecA[0] + vecA[1] <= vecA[n - 1]) {
            cout << "1 2 " << n << "\n";
        } else {
            cout << "-1\n";
        }

    }
}

int main() {
    Task();
    Solve();
}

