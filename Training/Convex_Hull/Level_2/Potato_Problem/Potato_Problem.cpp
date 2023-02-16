#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, index;
    bool joined;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point p) { return y != p.y ? y < p.y : x < p.x; }
    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }

    ll area(point pa, point pb) { return abs(((ll)pa.x - x) * (pb.y - y) - ((ll)pa.y - y) * (pb.x - x)); }
};

int T, n;
vector <point> p, p1, p2;

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
    for (int i = n - 2, j = sz; i >= 0; --i) {
        if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) >= 0)  {
            while (sz > j && p[sz - 1].ccw(p[sz], pts[i]) < 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    p.resize(sz);
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
        p.clear();
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }

        p1 = Build_ConvexHull(p);
        if (!p.size()) {
            cout << "-1\n";
            continue;
        }
        p2 = Build_ConvexHull(p);

        int it = 0;
        for (int i = 0; i < p2.size(); ++i) {
            if (p1[0].area(p1[1], p2[i]) < p1[0].area(p1[1], p2[it])) {
                it = i;
            }
        }
        ll mina = p1[0].area(p1[1], p2[it]);
        for (int i = 1; i < p1.size(); ++i) {
            int ii = (i + 1) % p1.size();
            while (p1[i].area(p1[ii], p2[(it + 1) % p2.size()]) < p1[i].area(p1[ii], p2[it])) {
                it = (it + 1) % p2.size();
            }
            mina = min(mina, p1[i].area(p1[ii], p2[it]));
        }

        cout << Area(p1) - mina << "\n";
    }
}

int main() {
    Task();
    Solve();
}
