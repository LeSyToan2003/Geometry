#include <bits/stdc++.h>

using namespace std;

bool stop;
int n, a, b, ans;
vector <int> vecVertices, vecParent;
vector <vector <int>> vecAdj;
set <int> setPath;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS1(int u, int parent) {
    vecParent[u] = parent;
    if (!stop) {
        vecVertices.push_back(u);
    }
    if (u == a) {
        stop = true;
    }
    for (auto v : vecAdj[u]) {
        if (v == parent) continue;
        DFS1(v, u);
    }
    if (!stop) {
        vecVertices.pop_back();
    }
}

void DFS2(int u, int parent, int cnt) {
    ans = max(ans, cnt);
    for (auto v : vecAdj[u]) {
        if (v == parent) continue;
        if (setPath.find(v) != setPath.end()) {
            DFS2(v, u, cnt);
        } else {
            DFS2(v, u, cnt + 1);
        }
    }
}

void Solve() {
    cin >> n >> a >> b;
    if (a == b) {
        return void(cout << 0);
    }
    vecAdj.resize(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        vecAdj[u].push_back(v);
        vecAdj[v].push_back(u);
    }
    vecParent.resize(n + 1);
    stop = false;
    DFS1(b, 0);
    int m = vecVertices.size();
    int c = vecVertices[(int)ceil(1.0 * m / 2)];
    for (int i = m - 1; i >= 0; --i) {
        setPath.insert(vecVertices[i]);
        if (vecVertices[i] == c) break;
    }
    ans = setPath.size();
    DFS2(c, vecParent[c], ans);
    cout << ans;
}

int main() {
    Task();
    Solve();
}
