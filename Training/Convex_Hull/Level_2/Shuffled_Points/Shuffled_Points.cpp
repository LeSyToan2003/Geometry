#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, index;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point p) { return y != p.y ? y < p.y : x < p.x; }
    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll norm2() { return (ll)x * x + (ll)y * y; }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

int n;
vector <ll> maxd(n);
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Build_ConvexHull(vector <point> &p) {
    sort(p.begin(), p.end());
    vector <point> pts = p;
    int n = p.size(), sz = 0;
    p.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || pts[0].ccw(pts[i], pts[n - 1]) > 0) {
            while (sz > 0 && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    for (int i = n - 2, j = sz; i >= 0; --i) {
        if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) > 0) {
            while (sz > j && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    p.resize(sz);
}

pair <ll, int> Mxdist(vector <point> points) {
    vector <point> p = points;
    Build_ConvexHull(p);
    pair <ll, int> result = {0, 0};
    int it = 0;
    for (int i = 0; i < p.size(); ++i) {
        while ((p[i] - p[it]).norm2() < (p[i] - p[(it + 1) % p.size()]).norm2()) {
            it = (it + 1) % p.size();
        }
        ll d = (p[i] - p[it]).norm2();
        int pos = max(p[i].index, p[it].index);
        if (d > result.first || (d == result.first && pos > result.second)) {
            result = {d, pos};
        }
    }
    return result;
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    maxd.resize(n);
    for (int i = 0; i < n; ++i) {
        p[i].index = i;
    }
    pair <ll, int> curr = {0, n};
    for (int i = n - 1; i >= 0; --i) {
        if (i < curr.second) {
            curr = Mxdist(p);
        }
        maxd[i] = curr.first;
        p.pop_back();
    }

    for (auto i : maxd) {
        cout << i << "\n";
    }
}

int main() {
    Task();
    Solve();
}
