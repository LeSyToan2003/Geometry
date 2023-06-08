#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll norm2() {
        return (ll)x * x + (ll)y * y;
    }
};

int n, m;
vector <point> vecP;
vector <vector <int>> vecEdge;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Processing() {
    vector <bool> vecVisit(n, false);
    vector <int> vecPar(n, 0);
    vector <ll> vecDist(n);
    for (int i = 1; i < n; ++i) {
        vecDist[i] = (vecP[0] - vecP[i]).norm2();
    }
    for (auto i : vecEdge[0]) {
        vecDist[i] = 0;
    }
    vecVisit[0] = true;
    for (int loop = 1; loop < n; ++loop) {
        pair <int, ll> minn = {- 1, 1e18};
        for (int i = 0; i < n; ++i) {
            if (!vecVisit[i] && vecDist[i] < minn.second) {
                minn = {i, vecDist[i]};
            }
        }
        int u = minn.first;
        vecVisit[u] = true;
        for (auto i : vecEdge[u]) {
            vecDist[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            if (!vecVisit[i]) {
                ll dist = (vecP[u] - vecP[i]).norm2();
                if (dist < vecDist[i]) {
                    vecDist[i] = dist;
                    vecPar[i] = u;
                }
            }
        }
        if (minn.second) {
            cout << vecPar[u] + 1 << " " << u + 1 << "\n";
        }
    }
}

void Solve() {
    cin >> n;
    vecP.resize(n), vecEdge.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        vecEdge[u].push_back(v);
        vecEdge[v].push_back(u);
    }
    Processing();
}

int main() {
    Task();
    Solve();
}
