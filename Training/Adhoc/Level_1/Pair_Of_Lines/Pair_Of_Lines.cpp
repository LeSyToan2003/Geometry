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
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool Check(int a, int b) {
    vector <point> vecPts;
    for (int i = 0; i < n; ++i) {
        if (vecP[i].ccw(vecP[a], vecP[b])) {
            vecPts.push_back(vecP[i]);
        }
    }
    if (vecPts.size() < 3) {
        return true;
    }
    for (int i = 2; i < vecPts.size(); ++i) {
        if (vecPts[0].ccw(vecPts[1], vecPts[i])) {
            return false;
        }
    }
    return true;
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    cout << ((Check(0, 1) || Check(0, 2) || Check(1, 2)) ? "YES" : "NO");
}

int main() {
    Task();
    Solve();
}
