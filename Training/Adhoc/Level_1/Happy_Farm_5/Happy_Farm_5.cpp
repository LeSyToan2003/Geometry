#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) {
    return !a ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator < (point p) {
        return y != p.y ? y < p.y : x < p.x;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }
};

int n;
ll len;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

vector <point> Build_ConvexHull(vector <point> vecP) {
    sort(vecP.begin(), vecP.end());
    int n = vecP.size();
    if (n < 3) {
        return vecP;
    }
    vector <point> vecPts = vecP;
    int sz = 0;
    vecP.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || vecPts[0].ccw(vecPts[i], vecPts[n - 1]) > 0) {
            while (sz > 0 && vecP[sz - 1].ccw(vecP[sz], vecPts[i]) <= 0) {
                sz--;
            }
            vecP[++sz] = vecPts[i];
        }
    }
    for (int i = n - 2, j = sz; i >= 0; --i) {
        if (i == 0 || vecPts[n - 1].ccw(vecPts[i], vecPts[0]) > 0) {
            while (sz > j && vecP[sz - 1].ccw(vecP[sz], vecPts[i]) <= 0) {
                sz--;
            }
            vecP[++sz] = vecPts[i];
        }
    }
    vecP.resize(sz);
    return vecP;
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    vecP = Build_ConvexHull(vecP);
    n = vecP.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        len += (ll)max(abs(vecP[i].x - vecP[ii].x), abs(vecP[i].y - vecP[ii].y));
    }
    len += 4;
    cout << len;
}

int main() {
    Task();
    Solve();
}
