#include <bits/stdc++.h>

using namespace std;

int n, m, k, l, r;
vector <bool> vecVisit;
vector <vector <pair <int, int>>> vecAdj;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS(int u) {
    vecVisit[u] = true;
    for (auto i : vecAdj[u]) {
        if (l <= i.second && i.second <= r || vecVisit[i.first]) continue;
        DFS(i.first);
    }
}

void Solve() {
    cin >> n >> m;
    vecAdj.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        vecAdj[u].push_back({v, i}), vecAdj[v].push_back({u, i});
    }
    cin >> k;
    while (k--) {
        cin >> l >> r;
        l--, r--;
        int cnt = 0;
        vecVisit.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (vecVisit[i]) continue;
            DFS(i);
            cnt++;
        }
        cout << cnt << "\n";
    }
}

int main() {
    Task();
    Solve();
}
