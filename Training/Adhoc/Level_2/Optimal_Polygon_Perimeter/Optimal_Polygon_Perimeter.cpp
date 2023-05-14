#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator != (point p) {
        return x != p.x || y != p.y;
    }

    int dist(point p) {
        return abs(x - p.x) + abs(y - p.y);
    }

    ll peri(point pa, point pb) {
        return (ll)dist(pa) + (ll)dist(pb) + (ll)pa.dist(pb);
    }
};

int n;
ll len1, len2;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    vector <point> vecPts = {point(1e9, 0), point(0, 1e9), point(- 1e9, 0), point(0, - 1e9)};
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
        if (vecP[i].x < vecPts[0].x) {
            vecPts[0] = vecP[i];
        }
        if (vecP[i].y < vecPts[1].y) {
            vecPts[1] = vecP[i];
        }
        if (vecP[i].x > vecPts[2].x) {
            vecPts[2] = vecP[i];
        }
        if (vecP[i].y > vecPts[3].y) {
            vecPts[3] = vecP[i];
        }
    }
    for (int i = 0; i < 4; ++i) {
        int ii = (i + 1) % 4;
        len2 += vecPts[i].dist(vecPts[ii]);
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            for (auto p : vecP) {
                if (p != vecPts[i] && p != vecPts[j]) {
                    len1 = max(len1, p.peri(vecPts[i], vecPts[j]));
                }
            }
        }
    }
    cout << len1 << " ";
    for (int i = 4; i <= n; ++i) {
        cout << len2 << " ";
    }
}

int main() {
    Task();
    Solve();
}
