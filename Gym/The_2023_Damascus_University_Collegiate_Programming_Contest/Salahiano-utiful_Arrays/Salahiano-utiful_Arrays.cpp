#include <bits/stdc++.h>

using namespace std;

bool valid;
int T, n;
vector <int> vecColor, vecCnt;
vector <vector <pair <int, int>>> vecAdj;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void DFS(int u, int color) {
    if (!valid) {
        return;
    }
    vecColor[u] = color;
    vecCnt[color]++;
    for (auto e : vecAdj[u]) {
        if (!valid) {
            return;
        }
        int v = e.first, w = e.second;
        if (vecColor[v] != - 1) {
            if (vecColor[v] != (color ^ w)) {
                valid = false;
            }
        } else {
            DFS(v, color ^ w);
        }
    }
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        vector <vector <pair <int, int>>> vecI(n * 2 + 1);
        for (int i = 1; i <= n; ++i) {
            int a, b;
            cin >> a >> b;
            vecI[a].push_back({i, 0});
            vecI[b].push_back({i, 1});
        }
        vecAdj.clear();
        vecAdj.resize(n + 1);
        valid = true;
        for (int i = 1; i <= n * 2; ++i) {
            if (vecI[i].size() >= 3) {
                valid = false;
                break;
            } else if (vecI[i].size() == 2) {
                int u = vecI[i][0].first, v = vecI[i][1].first;
                if (vecI[i][0].second == vecI[i][1].second) {
                    vecAdj[u].push_back({v, 1});
                    vecAdj[v].push_back({u, 1});
                } else {
                    vecAdj[u].push_back({v, 0});
                    vecAdj[v].push_back({u, 0});
                }
            }
        }
        if (!valid) {
            cout << "-1\n";
            continue;
        }
        vecColor.assign(n + 1, - 1);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (vecColor[i] != - 1) {
                continue;
            }
            vecCnt.assign(2, 0);
            DFS(i, 0);
            if (!valid) {
                break;
            }
            ans += min(vecCnt[0], vecCnt[1]);
        }
        cout << (valid ? ans : - 1) << "\n";
    }
}

int main() {
    Task();
    Solve();
}
