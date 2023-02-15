#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point p) { return x != p.x ? x < p.x : y < p.y; }
    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

int T, n, maxd;
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
        if (i == n - 1 || pts[0].ccw(pts[i], pts[n - 1]) < 0) {
            while (sz > 0 && p[sz - 1].ccw(p[sz], pts[i]) >= 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    p.resize(sz + 1);
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        p.clear();
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].y;
            p[i].x = i;
        }

        Build_ConvexHull(p);

        maxd = 0;
        for (int i = 1; i < p.size(); ++i) {
            maxd = max(maxd, p[i].x - p[i - 1].x);
        }

        cout << maxd << "\n";
    }
}

int main() {
    Task();
    Solve();
}
