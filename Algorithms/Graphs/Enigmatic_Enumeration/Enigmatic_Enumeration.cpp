#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m, minn;
vector <vector <int>> vecAdj, vecDist, vecCnt;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void BFS(int i) {
    vecDist[i][i] = 0;
    vecCnt[i][i] = 1;
    queue <int> queueV;
    queueV.push(i);
    while(!queueV.empty()) {
        int u = queueV.front();
        queueV.pop();
        for (auto v : vecAdj[u]) {
            if (vecDist[i][v] == vecDist[i][u]) {
                minn = min(minn, vecDist[i][u] * 2 + 1);
            } else if (vecDist[i][v] == vecDist[i][u] + 1) {
                minn = min(minn, vecDist[i][v] * 2);
                vecCnt[i][v] += vecCnt[i][u];
            } else if (vecDist[i][v] > vecDist[i][u] + 1) {
                vecDist[i][v] = vecDist[i][u] + 1;
                vecCnt[i][v] = vecCnt[i][u];
                queueV.push(v);
            }
        }
    }
}

void Solve() {
    cin >> n >> m;
    vecAdj.resize(n + 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        vecAdj[u].push_back(v);
        vecAdj[v].push_back(u);
    }
    vecDist.assign(n + 1, vector <int> (n + 1, 1e9));
    vecCnt.assign(n + 1, vector <int> (n + 1, 0));
    minn = 1e9;
    for (int i = 1; i <= n; ++i) {
        BFS(i);
    }
    ll ans = 0;
    for (int i = 1; i + 1 <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (vecDist[i][j] != minn / 2) continue;
            if (minn % 2) {
                for (auto k : vecAdj[j]) {
                    if (vecDist[i][k] != vecDist[i][j]) continue;
                    ans += (ll)vecCnt[i][j] * vecCnt[i][k];
                }
            } else {
                ans += (ll)vecCnt[i][j] * (vecCnt[i][j] - 1);
            }
        }
    }
    ans /= minn;
    cout << ans;
}

int main() {
    Task();
    Solve();
}
