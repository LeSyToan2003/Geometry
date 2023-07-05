#include <bits/stdc++.h>

using namespace std;

int n, m;
vector <bool> vecVisit;
vector <vector <vector <int>>> vecEdge;
stack <int> stackV;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS(int u, int id) {
    vecVisit[u] = true;
    for (auto v : vecEdge[id][u]) {
        if (vecVisit[v]) continue;
        DFS(v, id);
    }
    if (!id) {
        stackV.push(u);
    }
}

int Processing() {
    vecVisit.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (vecVisit[i]) continue;
        DFS(i, 0);
    }
    int cnt = 0;
    vecVisit.assign(n, false);
    while (!stackV.empty()) {
        int u = stackV.top();
        stackV.pop();
        if (vecVisit[u]) continue;
        DFS(u, 1);
        cnt++;
    }
    return cnt;
}

void Solve() {
    cin >> n >> m;
    vecEdge.assign(2, vector <vector <int>> (n));
    while (m--) {
        int u, v;
        cin >> u >> v;
        vecEdge[0][--u].push_back(--v);
        vecEdge[1][v].push_back(u);
    }
    cout << Processing();
}

int main() {
    Task();
    Solve();
}
