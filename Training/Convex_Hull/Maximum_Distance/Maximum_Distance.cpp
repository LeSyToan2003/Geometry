#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int blk = 999;
const int blksz = 209;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y;

    point() {}
    point(int a, int b) { x = a, y = b; }

    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll norm2() { return (ll)x * x + (ll)y * y; }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

bool operator < (point pa, point pb) { return pa.y != pb.y ? pa.y < pb.y : pa.x < pb.x; }

struct convexhull {
    vector <point> lef, rig;

    convexhull() {}
    convexhull(vector <point> &p) { lef = p; rig = p; Build_ConvexHull(); }

    convexhull operator + (convexhull ch) {
        convexhull result;
        result.lef.resize(lef.size() + ch.lef.size());
        merge(lef.begin(), lef.end(), ch.lef.begin(), ch.lef.end(), result.lef.begin());
        result.rig.resize(rig.size() + ch.rig.size());
        merge(rig.begin(), rig.end(), ch.rig.begin(), ch.rig.end(), result.rig.begin());
        result.Build_ConvexHull();
        return result;
    }

    void Build_ConvexHull() {
        int sz = 0;
        for (int i = 1; i < lef.size(); ++i) {
            while (sz > 0 && lef[sz - 1].ccw(lef[sz], lef[i]) <= 0) { sz--; }
            lef[++sz] = lef[i];
        }
        lef.resize(sz + 1);
        sz = 0;
        for (int i = 1; i < rig.size(); ++i) {
            while (sz > 0 && rig[sz - 1].ccw(rig[sz], rig[i]) >= 0) { sz--; }
            rig[++sz] = rig[i];
        }
        rig.resize(sz + 1);
    }

    ll MXDIST() {
        vector <point> p = lef;
        for (int i = rig.size() - 2; i > 0; --i) { p.push_back(rig[i]); }
        ll result = 0;
        int it = 0;
        for (int i = 0; i < p.size(); ++i) {
            while ((p[i] - p[it]).norm2() < (p[i] - p[(it + 1) % p.size()]).norm2()) { it = (it + 1) % p.size(); }
            result = max(result, (p[i] - p[it]).norm2());
        }
        return result;
    }
};

int n, q;
vector <point> p;
vector <pair <point, int>> block[blk];
convexhull RMQ[blk][19];

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Build_RMQ(vector <point> &p) {
    for (int i = 0; i < p.size(); ++i) { block[i / blksz].push_back({p[i], i}); }
    int n = (p.size() - 1) / blksz;
    for (int i = n; i >= 0; --i) {
        sort(block[i].begin(), block[i].end());
        vector <point> pts;
        for (auto j : block[i]) { pts.push_back(j.first); }
        RMQ[i][0] = convexhull(pts);
        for (int j = 1; i + (int)pow(2, j) - 1 <= n; ++j) {
            RMQ[i][j] = RMQ[i][j - 1] + RMQ[i + (int)pow(2, j - 1)][j - 1];
        }
    }
}

ll Get_RMQ(int l, int r) {
    int st = l / blksz, en = r / blksz;
    vector <point> p;
    for (auto i : block[st]) {
        if (i.second >= l && i.second <= r) {
            p.push_back(i.first);
        }
    }
    if (st == en) { return convexhull(p).MXDIST(); }
    int sz = p.size();
    for (auto i : block[en]) {
        if (i.second >= l && i.second <= r) {
            p.push_back(i.first);
        }
    }
    inplace_merge(p.begin(), p.begin() + sz, p.end());
    convexhull ch = convexhull(p);
    st++; en--;
    if (st <= en) {
        int j = (int)log2(en - st + 1);
        ch = ch + RMQ[st][j] + RMQ[en - (int)pow(2, j) + 1][j];
    }
    return ch.MXDIST();
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    Build_RMQ(p);

    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << Get_RMQ(a, b) << "\n";
    }
}

int main() {
    Task();
    Solve();
}
