#include <bits/stdc++.h>

using namespace std;

int n, x, y, len;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    while (n--) {
        cin >> x >> y;
        len = max(len, x + y);
    }
    cout << len;
}

int main() {
    Task();
    Solve();
}
