#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ld norm() {
        return hypot(x, y);
    }
};

int n, k;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n >> k;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    ld sumd = 0;
    for (int i = 0; i + 1 < n; ++i) {
        sumd += (vecP[i] - vecP[i + 1]).norm();
    }
    cout << fixed << setprecision(10) << sumd * k / 50;
}

int main() {
    Task();
    Solve();
}
