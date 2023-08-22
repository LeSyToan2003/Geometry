#include <bits/stdc++.h>

using namespace std;

int n, r, m, w;
vector <bool> vecVisit;
vector <int> vecMatch;
vector <string> vecS;
vector <vector <int>> vecAdj;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool DFS(int u) {
    if (vecVisit[u]) {
        return false;
    }
    vecVisit[u] = true;
    for (auto v : vecAdj[u]) {
        if (!vecMatch[v] || DFS(vecMatch[v])) {
            vecMatch[v] = u;
            return true;
        }
    }
    return false;
}

void Solve() {
    cin >> n;
    vecS.resize(n + 1);
    map <string, int> mapS;
    for (int i = 1; i <= n; ++i) {
        cin >> vecS[i];
        mapS[vecS[i]] = i;
    }
    vector <vector <bool>> vecGraph(n + 1, vector <bool> (n + 1, true));
    cin >> r;
    while (r--) {
        int m, w;
        cin >> m >> w;
        vector <bool> vecStatus(n + 1, false);
        while (m--) {
            string s;
            cin >> s;
            int u = mapS[s];
            vecStatus[u] = true;
            for (int v = 1; v < w; ++v) {
                vecGraph[u][v] = false;
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (!vecStatus[i]) {
                vecGraph[i][w] = false;
            }
        }
    }
    vecAdj.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (vecGraph[i][j]) {
                vecAdj[i].push_back(j);
            }
        }
    }
    vecMatch.assign(n + 1, 0), vecVisit.assign(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        DFS(i);
    }
    for (int i = 1; i <= n; ++i) {
        cout << vecS[vecMatch[i]] << " ";
    }
}

int main() {
    Task();
    Solve();
}
