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
    vector <ll> vecA;
    ll sum = 0;
    for (auto v : vecAdj[u]) {
        if (v == parent) continue;
        DFS(v, u);
        sum += vecDP[v][0];
        vecA.push_back(vecDP[v][1] - vecDP[v][0]);
    }
    vecDP[u][0] = sum + (ll)vecValue[1];
    vecDP[u][1] = sum + (ll)vecValue[0];
    sort(vecA.begin(), vecA.end(), greater <ll> ());
    int cnt = 1;
    for (auto i : vecA) {
        cnt++;
        sum += i;
        vecDP[u][0] = max(vecDP[u][0], sum + (ll)vecValue[cnt]);
        vecDP[u][1] = max(vecDP[u][1], sum + (ll)vecValue[cnt - 1]);
    }
}

void Solve() {
    cin >> n;
    vecValue.resize(n), vecAdj.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> vecValue[i];
    }
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        vecAdj[u].push_back(v);
        vecAdj[v].push_back(u);
    }
    vecDP.assign(n + 1, vector <ll> (2));
    DFS(1, 0);
    cout << vecDP[1][1];
}

int main() {
    Task();
    Solve();
}
