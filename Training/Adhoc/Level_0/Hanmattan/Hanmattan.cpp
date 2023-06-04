#include <bits/stdc++.h>

using namespace std;

int xa, ya, xs, ys, xb, yb;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> xa >> ya >> xs >> ys >> xb >> yb;
    cout << (min(xa, xs) <= xb && xb <= max(xa, xs) && min(ya, ys) <= yb && yb <= max(ya, ys) ? "Yes" : "No");
}

int main() {
    Task();
    Solve();
}
