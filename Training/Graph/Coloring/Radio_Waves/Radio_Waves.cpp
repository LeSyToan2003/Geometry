#include <bits/stdc++.h>

using namespace std;

typedef double db;

const db eps = 1e-9;

bool geq(db a, db b) {
    return a >= b - eps;
}

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    db norm() {
        return hypot(x, y);
    }
};

bool chk;
int n;
vector <bool> visited;
vector <int> ans, color;
vector <point> vecP;
vector <vector <int>> vecEdge;
vector <vector <db>> vecD;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);
}

void DFS(int u, int c) {
    if (!chk) {
        return;
    }
    visited[u] = true;
    color[u] = c;
    for (auto v : vecEdge[u]) {
        if (!chk) {
            return;
        }
        if (visited[v]) {
            if (color[v] == c) {
                chk = false;
                return;
            }
        } else {
            DFS(v, c ^ 1);
        }
    }
}

bool Check(db r) {
    vecEdge.clear();
    vecEdge.resize(n);
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (geq(r * 2, vecD[i][j])) {
                vecEdge[i].push_back(j);
                vecEdge[j].push_back(i);
            }
        }
    }
    visited.assign(n, false);
    color.assign(n, - 1);
    chk = true;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            DFS(i, 0);
            if (!chk) {
                break;
            }
        }
    }
    if (chk) {
        ans = color;
    }
    return chk;
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    db l = 1e9, r = 0;
    vecD.resize(n);
    for (int i = 0; i < n; ++i) {
        vecD[i].resize(n);
    }
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            vecD[i][j] = (vecP[i] - vecP[j]).norm();
            l = min(l, vecD[i][j] / 2);
            r = max(r, vecD[i][j] / 2);
        }
    }
    vecEdge.resize(n);
    int loop = 0;
    while (++loop <= 100) {
        db m = (l + r) / 2;
        if (Check(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << fixed << setprecision(10) << l << "\n";
    for (auto i : ans) {
        cout << i + 1 << " ";
    }
}

int main() {
    Task();
    Solve();
}
