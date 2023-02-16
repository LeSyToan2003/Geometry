#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, index;
    bool joined;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point a) { return y != a.y ? y < a.y : x < a.x; }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    ll operator * (point p) { return (ll)x * p.x + (ll)y * p.y; }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }

    bool on(point pa, point pb) { return ccw(pa, pb) ? false : (pa - *this) * (pb - *this) <= 0; }

    bool insp(vector <point> &p) {
        int n = p.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            point u = p[i], v = p[ii];
            if (u.y < v.y) { swap(u, v); }
            if (v.y < y && y <= u.y && ccw(u, v) < 0) { cnt ^= 1; }
        }
        return cnt;
    }

    bool incp(vector <point> &p) {
        if (on(p[0], p[1]) || on(p[0], p.back())) { return false; }
        int l = 2, r = p.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(p[0], p[m]) <= 0) { r = m; }
            else { l = m + 1; }
        }
        if (on(p[r - 1], p[r])) { return false; }
        vector <point> tri = {p[0], p[r - 1], p[r]};
        return insp(tri);
    }
};

int T, n, q;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

vector <point> Build_ConvexHull(vector <point> &p) {
    vector <point> result;
    sort(p.begin(), p.end());
    if (p.size() < 3) {
        result = p;
        p.clear();
        return result;
    }
    bool chk = true;
    for (int i = 2; i < p.size(); ++i) {
        if (p[0].ccw(p[1], p[i])) {
            chk = false;
            break;
        }
    }
    if (chk) {
        p[1] = p.back();
        p.resize(2);
        result = p;
        p.clear();
        return result;
    }
    for (int i = 0; i < p.size(); ++i) {
        p[i].index = i;
        p[i].joined = false;
    }
    vector <point> pts = p;
    int n = p.size(), sz = 0;
    p.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || pts[0].ccw(pts[i], pts[n - 1]) >= 0) {
            while (sz > 0 && p[sz - 1].ccw(p[sz], pts[i]) < 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    if (sz != n - 1) {
        for (int i = n - 2, j = sz; i >= 0; --i) {
            if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) >= 0) {
                while (sz > j && p[sz - 1].ccw(p[sz], pts[i]) < 0) {
                    sz--;
                }
                p[++sz] = pts[i];
            }
        }
        p.resize(sz);
    }
    else {
        p.resize(sz + 1);
    }
    for (int i = 0; i < p.size(); ++i) {
        pts[p[i].index].joined = true;
    }
    result = p;
    p.clear();
    for (int i = 0; i < n; ++i) {
        if (!pts[i].joined) {
            p.push_back(pts[i]);
        }
    }
    return result;
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n >> q;
        p.clear();
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }

        vector <vector <point>> layers;
        while (p.size()) {
            layers.push_back(Build_ConvexHull(p));
        }

        while (q--) {
            point candle;
            cin >> candle.x >> candle.y;
            int l = 0, r = layers.size() - 1;
            while (l < r) {
                int m = (l + r) / 2;
                if (l == m) {
                    m++;
                }
                if (candle.incp(layers[m])) {
                    l = m;
                }
                else {
                    r = m - 1;
                }
            }
            cout << (l == 0 && !candle.incp(layers[0]) ? 0 : l + 1) << "\n";
        }
    }
}

int main() {
    Task();
    Solve();
}
