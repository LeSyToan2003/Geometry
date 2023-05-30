#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld eps = 1e-9;
const ld pi = acos(- 1);

bool leq(ld a, ld b) {
    return a <= b + eps;
}

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator < (point p) {
        return updown() != p.updown() ? updown() < p.updown() : y * p.x < x * p.y;
    }

    bool updown() {
        return y > 0 || (y == 0 && x < 0);
    }

    ld angle(point p) {
        ld a = atan2(y, x), b = atan2(p.y, p.x);
        return (a <= b ? b - a : pi * 2 - (a - b));
    }
};

int n;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    sort(vecP.begin(), vecP.end());
    int j = 0, cnt = 1, maxx = 0;
    for (int i = 0; i < n; ++i) {
        while ((j + 1) % n != i && leq(vecP[i].angle(vecP[(j + 1) % n]), pi / 4)) {
            j = (j + 1) % n;
            cnt++;
        }
        maxx = max(maxx, cnt);
        if (i == j) {
            j = (j + 1) % n;
            cnt++;
        }
        cnt--;
    }
    cout << maxx;
}

int main() {
    Task();
    Solve();
}
