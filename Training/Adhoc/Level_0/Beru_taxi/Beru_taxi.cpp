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

int n, v;
ld minn;
point home, taxi;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    minn = 1e9;
    cin >> home.x >> home.y >> n;
    while (n--) {
        cin >> taxi.x >> taxi.y >> v;
        minn = min(minn, (home - taxi).norm() / v);
    }
    cout << fixed << setprecision(10) << minn;
}

int main() {
    Task();
    Solve();
}

