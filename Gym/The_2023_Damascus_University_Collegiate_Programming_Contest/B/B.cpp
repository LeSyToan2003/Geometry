#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct persistent_dsu {
    vector <int> vecParent, vecSize, vecTime;
    vector <vector <pair <int, int>>> vecCnt;
    vector <set <int>> setIndex;

    persistent_dsu() {}
    persistent_dsu(vector <int> vecA) {
        int n = vecA.size() - 1;
        vecParent.resize(n + 1), vecSize.assign(n + 1, 1), vecTime.assign(n + 1, 0);
        vecCnt.resize(n + 1), setIndex.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            vecParent[i] = i;
            vecCnt[i].push_back({0, 1});
            setIndex[i].insert(vecA[i]);
        }
    }

    int findParent(int u) {
        return u == vecParent[u] ? u : findParent(vecParent[u]);
    }

    int findParent(int u, int t) {
        return u == vecParent[u] || vecTime[u] > t ? u : findParent(vecParent[u], t);
    }

    void unionSet(int u, int v, int t) {
        int a = findParent(u), b = findParent(v);
        if (a == b) {
            return;
        }
        if (vecSize[a] < vecSize[b]) {
            swap(a, b);
        }
        vecSize[a] += vecSize[b];
        vecParent[b] = a;
        vecTime[b] = t;
        int cnt = vecCnt[a].back().second;
        for (auto i : setIndex[b]) {
            if (setIndex[a].find(i) != setIndex[a].end()) {
                continue;
            }
            bool pre = setIndex[a].find(i - 1) != setIndex[a].end();
            bool nxt = setIndex[a].find(i + 1) != setIndex[a].end();
            if (!pre && !nxt) {
                cnt++;
            } else if (pre && nxt) {
                cnt--;
            }
            setIndex[a].insert(i);
        }
        vecCnt[a].push_back({t, cnt});
    }

    int findCnt(int u, int t) {
        int a = findParent(u, t);
        auto it = upper_bound(vecCnt[a].begin(), vecCnt[a].end(), make_pair(t, INF));
        it--;
        return (*it).second;
    }
};

int n, q;
vector <int> vecA;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n >> q;
    vecA.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> vecA[i];
    }
    persistent_dsu PDSU = persistent_dsu(vecA);
    vector <int> vecAns(q + 1, 1);
    for (int i = 1; i <= q; ++i) {
        int typee;
        cin >> typee;
        if (typee == 1) {
            int u, v, x;
            cin >> u >> v >> x;
            x = vecAns[x];
            u = (1LL * u * x) % n + 1;
            v = (1LL * v * x) % n + 1;
            PDSU.unionSet(u, v, i);
        } else {
            int u, t, x;
            cin >> u >> t >> x;
            x = vecAns[x];
            u = (1LL * u * x) % n + 1;
            t = (1LL * t * x) % i + 1;
            vecAns[i] = PDSU.findCnt(u, t);
            cout << vecAns[i] << "\n";
        }
    }
}

int main() {
    Task();
    Solve();
}
