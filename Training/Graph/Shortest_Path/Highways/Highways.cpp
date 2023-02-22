#include <bits/stdc++.h>

using namespace std;

const int MAXD = 1e9;

struct point {
    int x, y;

    point() {}
    point(int a, int b) { x = a, y = b; }

    point operator - (point p) { return point(x - p.x, y - p.y); }

    int norm2() { return x * x + y * y; }
};

int n, m;
vector <point> p;
vector <vector <int>> edge;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Find_MST() {
    vector <int> d(n + 1), par(n + 1, 1);
    for (int i = 2; i <= n; ++i) { d[i] = (p[1] - p[i]).norm2(); }
    for (auto i : edge[1]) { d[i] = 0; }
    vector <bool> visited(n + 1, false);
    visited[1] = true;
    for (int i = 2; i <= n; ++i) {
        pair <int, int> minn = {0, MAXD};
        for (int j = 2; j <= n; ++j) {
            if (!visited[j] && d[j] < minn.second) {
                minn = {j, d[j]};
            }
        }
        visited[minn.first] = true;
        for (auto j : edge[minn.first]) { d[j] = 0; }
        for (int j = 2; j <= n; ++j) {
            if (!visited[j]) {
                int can = (p[minn.first] - p[j]).norm2();
                if (can < d[j]) {
                    d[j] = can;
                    par[j] = minn.first;
                }
            }
        }
        if (minn.second) { cout << minn.first << " " << par[minn.first] << "\n"; }
    }
}

void Solve() {
    cin >> n;
    p.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    cin >> m;
    edge.resize(n + 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    Find_MST();
}

int main() {
    Task();
    Solve();
}
