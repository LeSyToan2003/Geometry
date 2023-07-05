#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k, ans;
vector <bool> vecVisit;
vector <int> vecChild, vecMaxDist;
vector <vector <int>> vecDist;
vector <vector <pair <int, int>>> vecEdge;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS1(int u, int parent) {
    vecChild[u] = 1;
    for (auto e : vecEdge[u]) {
        int v = e.first;
        if (v == parent || vecVisit[v]) continue;
        DFS1(v, u);
        vecChild[u] += vecChild[v];
    }
}

int DFS2(int u, int parent, int m) {
    for (auto e : vecEdge[u]) {
        int v = e.first;
        if (v == parent || vecVisit[v] || vecChild[v] <= m / 2) continue;
        return DFS2(v, u, m);
    }
    return u;
}

void DFS3(int u, int parent, int d, int l, int id) {
    if (d <= k) {
        ans = max(ans, l + vecMaxDist[k - d]);
    } else {
        return;
    }
    if (vecDist[id].size() <= d) {
        vecDist[id].push_back(l);
    } else {
        vecDist[id][d] = max(vecDist[id][d], l);
    }
    for (auto e : vecEdge[u]) {
        int v = e.first, w = e.second;
        if (v == parent || vecVisit[v]) continue;
        DFS3(v, u, d + 1, l + w, id);
    }
}

void GetPath(int u, int m) {
    vecMaxDist.assign(k + 1, 0);
    vecDist.clear();
    vecDist.resize(m + 9);
    for (int i = 0; i < vecEdge[u].size(); ++i) {
        int v = vecEdge[u][i].first, w = vecEdge[u][i].second;
        if (vecVisit[v]) continue;
        vecDist[i].push_back(0);
        DFS3(v, u, 1, w, i);
        for (int j = 1; j < vecDist[i].size(); ++j) {
            vecMaxDist[j] = max(vecMaxDist[j], vecDist[i][j]);
        }
    }
}

void Processing(int u) {
    DFS1(u, - 1);
    int m = vecChild[u], centroid = DFS2(u, - 1, m);
    if (m - 1 >= k) {
        GetPath(centroid, m);
    }
    vecVisit[centroid] = true;
    for (auto e : vecEdge[centroid]) {
        int v = e.first;
        if (vecVisit[v]) continue;
        Processing(v);
    }
}

void Solve() {
    cin >> n >> k;
    k--;
    vecEdge.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        vecEdge[--u].push_back({--v, w});
        vecEdge[v].push_back({u, w});
    }
    vecChild.resize(n);
    vecVisit.assign(n, false);
    Processing(0);
    cout << ans;
}

int main() {
    Task();
    Solve();
}
