#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector <int> vecValue;
vector <vector <int>> vecAdj;
vector <vector <ll>> vecDP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS(int u, int parent) {
    vecDP[0][u] = 0;
    vecDP[1][u] = (ll)vecValue[u];
    for (auto v : vecAdj[u]) {
        if (v == parent) continue;
        DFS(v, u);
        vecDP[0][u] += max(vecDP[0][v], vecDP[1][v]);
        vecDP[1][u] += vecDP[0][v];
    }
}

void Solve() {
    cin >> n;
    vecAdj.resize(n + 1), vecValue.resize(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        vecAdj[u].push_back(v);
        vecAdj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> vecValue[i];
    }
    vecDP.assign(2, vector <ll> (n + 1));
    DFS(1, 0);
    cout << max(vecDP[0][1], vecDP[1][1]);
}

int main() {
    Task();
    Solve();
}
