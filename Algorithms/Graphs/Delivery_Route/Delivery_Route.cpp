#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int n, x, y, s, nCC;
vector <bool> vecVisit;
vector <int> vecId, vecTopo;
vector <pair <int, int>> vecEdge;
vector <vector <int>> vecCC, vecAdj2;
vector <vector <vector <pair <int, int>>>> vecAdj1;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS1(int u) {
    vecCC[nCC].push_back(u);
    vecId[u] = nCC;
    for (auto e : vecAdj1[u][0]) {
        int v = e.first;
        if (vecId[v]) continue;
        DFS1(v);
    }
}

void DFS2(int u) {
    vecVisit[u] = true;
    for (auto v : vecAdj2[u]) {
        if (vecVisit[v]) continue;
        DFS2(v);
    }
    vecTopo.push_back(u);
}

void Solve() {
    cin >> n >> x >> y >> s;
    vecAdj1.assign(n + 1, vector <vector <pair <int, int>>> (2));
    while (x--) {
        int u, v, w;
        cin >> u >> v >> w;
        vecAdj1[u][0].push_back({v, w});
        vecAdj1[v][0].push_back({u, w});
    }
    while (y--) {
        int u, v, w;
        cin >> u >> v >> w;
        vecAdj1[u][1].push_back({v, w});
        vecEdge.push_back({u, v});
    }
    vecCC.resize(n + 1);
    vecId.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (vecId[i]) continue;
        nCC++;
        DFS1(i);
    }
    vecAdj2.resize(nCC + 1);
    for (auto e : vecEdge) {
        int u = e.first, v = e.second;
        vecAdj2[vecId[u]].push_back(vecId[v]);
    }
    vecVisit.assign(nCC + 1, false);
    for (int i = 1; i <= nCC; ++i) {
        if (vecVisit[i]) continue;
        DFS2(i);
    }
    reverse(vecTopo.begin(), vecTopo.end());
    vector <int> vecDist(n + 1, INF);
    vecDist[s] = 0;
    for (auto cc : vecTopo) {
        priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pqV;
        for (auto u : vecCC[cc]) {
            if (vecDist[u] == INF) continue;
            pqV.push({vecDist[u], u});
        }
        while (!pqV.empty()) {
            int u = pqV.top().second, d = pqV.top().first;
            pqV.pop();
            if (d != vecDist[u]) continue;
            for (auto e : vecAdj1[u][0]) {
                int v = e.first, w = e.second;
                if (vecDist[v] > vecDist[u] + w) {
                    vecDist[v] = vecDist[u] + w;
                    pqV.push({vecDist[v], v});
                }
            }
        }
        for (auto u : vecCC[cc]) {
            if (vecDist[u] == INF) continue;
            for (auto e : vecAdj1[u][1]) {
                int v = e.first, w = e.second;
                vecDist[v] = min(vecDist[v], vecDist[u] + w);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (vecDist[i] == INF) {
            cout << "NO PATH\n";
        } else {
            cout << vecDist[i] << "\n";
        }
    }
}

int main() {
    Task();
    Solve();
}

