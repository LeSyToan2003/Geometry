#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 9;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    ll x, y;
    int index;

    point() {}
    point(ll a, ll b) { x = a, y = b; }

    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll det(point p) { return x * p.y - y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

int n, m, root, P[29][MAXN];
vector <int> par, h;
vector <point> p;

int high(int u) {
    if (u == root) { return h[u] = 1; }
    if (h[u] == 0) { h[u] = high(P[0][u]) + 1; }
    return h[u];
}

void initLCA() {
    for (int i = 1; i <= n; ++i) {
        P[0][i] = par[i];
        if (par[i] == 0) { root = i; }
    }
    for (int i = 1; i <= n; ++i) { h[i] = high(i); }
    for (int k = 1; k <= 19; ++k) {
        for (int i = 0; i < n; ++i) {
            P[k][i] = P[k - 1][P[k - 1][i]];
        }
    }
}

int LCA(int x, int y) {
    if (h[x] > h[y]) { swap(x, y); }
    for (int k = 19; k >= 0; --k) {
        if (h[P[k][y]] >= h[x]) {
            y = P[k][y];
        }
    }
    for (int k = 19; k >= 0; --k) {
        if (P[k][x] != P[k][y]) {
            x = P[k][x], y = P[k][y];
        }
    }
    while (x != y) { x = P[0][x], y = P[0][y]; }
    return x;
}

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    p.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    for (int i = 1; i <= n; ++i) {
        p[i].index = i;
    }
    par.resize(n + 1); h.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        par[i] = 0;
        h[i] = 0;
    }
    vector <point> points;
    points.push_back(p.back());
    for (int i = n - 1; i >= 1; --i) {
        while (points.size() > 1 && p[i].ccw(points.back(), points[points.size() - 2]) > 0) {
            points.pop_back();
        }
        par[i] = points.back().index;
        points.push_back(p[i]);
    }

    initLCA();

    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << " ";
    }
}

int main() {
    Task();
    Solve();
}
