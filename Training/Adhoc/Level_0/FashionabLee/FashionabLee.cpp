#include <bits/stdc++.h>

using namespace std;

int T, n;

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
        cout << (!(n % 4) ? "YES\n" : "NO\n");
    }
}

int main() {
    Task();
    Solve();
}
