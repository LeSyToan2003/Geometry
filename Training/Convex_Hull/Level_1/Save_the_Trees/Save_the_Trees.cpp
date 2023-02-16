#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y;

    point() {}
    point(int a, int b) { x = a; y = b; }

    bool operator < (point a) { return y != a.y ? y < a.y : x < a.x; }
    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

int T, n;
vector <int> a;
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
            while(sz > 0 && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    for (int i = n - 2, j = sz; i >= 0; --i) {
        if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) > 0) {
            while(sz > j && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    p.resize(sz);
}

ll Area(vector <point> &p) {
    ll area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        area += p[i].det(p[ii]);
    }
    return area;
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        a.clear();
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        p.clear();
        int miny = a.back(), maxy = a.back();
        for (int i = n - 2; i >= 0; --i) {
            p.push_back(point(a[i], miny));
            p.push_back(point(a[i], maxy));
            miny = min(miny, a[i]);
            maxy = max(maxy, a[i]);
        }

        Build_ConvexHull(p);

        cout << Area(p) << "\n";
    }
}

int main() {
    Task();
    Solve();
}
