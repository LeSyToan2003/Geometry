#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T, n;
vector <int> vecA;
vector <vector <int>> vecAdj;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

priority_queue <ll> DFS(int u, int parent) {
    priority_queue <ll> pqA;
    for (auto v : vecAdj[u]) {
        if (v == parent) {
            continue;
        }
        priority_queue <ll> pqB = DFS(v, u);
        if (pqA.size() < pqB.size()) {
            swap(pqA, pqB);
        }
        priority_queue <ll> pqC;
        while (!pqB.empty()) {
            pqC.push(pqA.top() + pqB.top());
            pqA.pop();
            pqB.pop();
        }
        while (!pqC.empty()) {
            pqA.push(pqC.top());
            pqC.pop();
        }
    }
    pqA.push(vecA[u]);
    return pqA;
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        vecA.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> vecA[i];
        }
        vecAdj.clear();
        vecAdj.resize(n + 1);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            vecAdj[u].push_back(v);
            vecAdj[v].push_back(u);
        }
        priority_queue <ll> pqA = DFS(1, 0);
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (!pqA.empty()) {
                ans += pqA.top();
                pqA.pop();
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
}

int main() {
    Task();
    Solve();
}
