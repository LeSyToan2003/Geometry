#include <bits/stdc++.h>

using namespace std;

int T;
vector <int> vecL;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> T;
    vecL.resize(3);
    while (T--) {
        for (int i = 0; i < 3; ++i) {
            cin >> vecL[i];
        }
        sort(vecL.begin(), vecL.end());
        if (vecL[0] + vecL[1] == vecL[2]) {
            cout << "YES\n";
        } else {
            cout << ((vecL[0] == vecL[1] && !(vecL[2] % 2)) || (vecL[1] == vecL[2] && !(vecL[0] % 2)) ? "YES\n" : "NO\n");
        }
    }
}

int main() {
    Task();
    Solve();
}

