#include <bits/stdc++.h>

using namespace std;

bool bridge;
int T, n, m;
vector <bool> vecVisit;
vector <int> vecOrder, vecLow;
vector <pair <int, int>> vecAns;
vector <vector <int>> vecAdj;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS(int u, int par) {
    if (bridge) {
        return;
    }
    vecVisit[u] = true;
    if (par == - 1) {
        vecOrder[u] = vecLow[u] = 1;
    } else {
        vecOrder[u] = vecLow[u] = vecOrder[par] + 1;
    }
    for (auto v : vecAdj[u]) {
        if (v == par || vecOrder[v] > vecOrder[u]) continue;
        if (vecVisit[v]) {
            vecLow[u] = min(vecLow[u], vecOrder[v]);
        } else {
            DFS(v, u);
        }
        vecAns.push_back({u + 1, v + 1});
        vecLow[u] = min(vecLow[u], vecLow[v]);
        if (vecLow[v] > vecOrder[u]) {
            bridge = true;
            return;
        }
    }
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n >> m;
        vecAdj.clear(), vecAns.clear();
        vecAdj.resize(n);
        while (m--) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            vecAdj[u].push_back(v);
            vecAdj[v].push_back(u);
        }
        vecVisit.assign(n, false), vecOrder.assign(n, 0), vecLow.assign(n, 0);
        bridge = false;
        DFS(0, - 1);
        if (bridge) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (auto edge : vecAns) {
                cout << edge.first << " " << edge.second << "\n";
            }
        }
    }
}

int main() {
    Task();
    Solve();
}
