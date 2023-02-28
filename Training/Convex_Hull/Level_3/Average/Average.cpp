#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct fraction {
    ll nume, deno;

    fraction() {}
    fraction(ll a, ll b) {
        ll g = __gcd(a, b);
        nume = a / g, deno = b / g;
    }
};

struct point {
    int x, y, index;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point p) { return y != p.y ? y < p.y : x < p.x; }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    ll operator * (point p) { return (ll)x * p.x + (ll)y * p.y; }

    ll norm2() { return (ll)x * x + (ll)y * y; }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }

    bool on(point pa, point pb) { return ccw(pa, pb) ? false : (pa - *this) * (pb - *this) <= 0; }

    bool insp(vector <point> &p) {
        int n = p.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            point pa = p[i], pb = p[ii];
            if (on(pa, pb)) { return true; }
            if (pa.y < pb.y) { swap(pa, pb); }
            if (pb.y < y && y <= pa.y && ccw(pa, pb) < 0) { cnt ^= 1; }
        }
        return cnt;
    }
};

int n;
ll cnt;
fraction avg;
point pst, pen;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool cmp(point pa, point pb) {
    ll A = (ll)pa.y * pb.x, B = (ll)pa.x * pb.y;
    if (A != B) { return A < B; }
    if (!pa.ccw(pst, pen)) { return pa.norm2() > pb.norm2(); }
    return pa.norm2() < pb.norm2();
}

void Build_ConvexHull(vector <point> &p) {
    sort(p.begin(), p.end());
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
        return;
    }
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

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    sort(p.begin(), p.end());
    for (int i = 1; i < n; ++i) {
        p[i] = p[i] - p[0];
    }
    p[0] = point(0, 0);
    pst = p[0], pen = p.back();
    sort(p.begin() + 1, p.end(), cmp);
    for (int i = 0; i < n; ++i) {
        p[i].index = i;
    }

    vector <point> polygon = p;
    Build_ConvexHull(polygon);
    int m = polygon.size();
    if (m == 2) {
        return void(cout << "2/1");
    }
    cnt = (ll)m * (n - m);

    vector <point> points;
    for (int i = 1; i < n; ++i) {
        points.push_back(p[i]);
    }
    Build_ConvexHull(points);
    int sz = points.size();
    cnt += (ll)sz;
    for (int i = 1; i < m; ++i) {
        int pre = (i - 1 + m) % m, nxt = (i + 1) % polygon.size();
        int curr = polygon[i].index, st = polygon[pre].index, en = polygon[nxt].index;
        vector <point> tri = {p[st], p[curr], p[en]}, pts = {p[st]};
        for (int j = (st + 1) % n; j != ((en + 1) % n); j = (j + 1) % n) {
            if (j != curr && p[j].insp(tri)) {
                pts.push_back(p[j]);
            }
        }
        Build_ConvexHull(pts);
        sz = pts.size();
        cnt += (ll)m - 1LL + (ll)sz - 2LL;
    }
    avg = fraction(cnt, n);

    cout << avg.nume << "/" << avg.deno;
}

int main() {
    Task();
    Solve();
}
