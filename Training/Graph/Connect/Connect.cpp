#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ld norm() {
        return hypot(x, y);
    }
};

int n;
ld W, C;
vector <int> vecParent, vecSize;
vector <pair <ld, pair <int, int>>> vecEdge;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

int Parent(int u) {
    return u == vecParent[u] ? u : vecParent[u] = Parent(vecParent[u]);
}

bool DSU(int u, int v) {
    int a = Parent(u), b = Parent(v);
    if (a == b) {
        return false;
    }
    if (vecSize[a] < vecSize[b]) {
        swap(a, b);
    }
    vecSize[a] += vecSize[b];
    vecParent[b] = a;
    return true;
}

ld FindMST() {
    sort(vecEdge.begin(), vecEdge.end());
    vecParent.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        vecParent[i] = i;
    }
    vecSize.assign(n + 1, 1);
    ld ans1 = W * n, ans2 = 0;
    for (auto e : vecEdge) {
        ld w = e.first;
        int u = e.second.first, v = e.second.second;
        if (!DSU(u, v)) {
            continue;
        }
        if (w < W) {
            ans1 += w - W;
        }
        ans2 += w;
    }
    return min(ans1, ans2);
}

void Solve() {
    cin >> n;
    vecP.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    cin >> W >> C;
    for (int i = 1; i + 1 <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            vecEdge.push_back({C * (vecP[i] - vecP[j]).norm(), {i, j}});
        }
    }
    cout << fixed << setprecision(10) << FindMST();
}

int main() {
    Task();
    Solve();
}
