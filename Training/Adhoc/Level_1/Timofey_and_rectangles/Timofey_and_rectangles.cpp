#include <bits/stdc++.h>

using namespace std;

int n, x1, y1, x2, y2;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cout << "YES\n";
    cin >> n;
    while (n--) {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << 2 * (abs(x1) % 2) + (abs(y1) % 2) + 1 << "\n";
    }
}

int main() {
    Task();
    Solve();
}
