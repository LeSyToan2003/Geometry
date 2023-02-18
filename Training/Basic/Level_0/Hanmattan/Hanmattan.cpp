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

    int minx = min(xa, xs);
    int miny = min(ya, ys);
    int maxx = max(xa, xs);
    int maxy = max(ya, ys);

    cout << (minx <= xb && xb <= maxx && miny <= yb && yb <= maxy ? "Yes" : "No");
}

int main() {
    Task();
    Solve();
}
