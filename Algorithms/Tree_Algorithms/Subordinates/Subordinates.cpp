#include <bits/stdc++.h>

using namespace std;

int n;
vector <int> vecChild;
vector <vector <int>> vecEdge;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS(int u, int parent) {
    vecChild[u] = 1;
    for (auto v : vecEdge[u]) {
        if (v == parent) continue;
        DFS(v, u);
        vecChild[u] += vecChild[v];
    }
}

void Solve() {
    cin >> n;
    vecEdge.resize(n + 1), vecChild.resize(n + 1);
    for (int i = 2; i <= n; ++i) {
        int u;
        cin >> u;
        vecEdge[i].push_back(u);
        vecEdge[u].push_back(i);
    }
    DFS(1, 0);
    for (int i = 1; i <= n; ++i) {
        cout << vecChild[i] - 1 << " ";
    }
}

int main() {
    Task();
    Solve();
}
