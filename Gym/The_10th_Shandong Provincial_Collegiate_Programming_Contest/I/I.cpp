#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct segmenttree {
    vector <int> vecMin, vecCnt, vecLazy;

    segmenttree() {}
    segmenttree(int n) {
        vecMin.resize(n * 4), vecCnt.resize(n * 4), vecLazy.resize(n * 4);
        build(0, 1, n);
    }

    void mergeChild(int id) {
        int left = id * 2 + 1, right = id * 2 + 2;
        vecMin[id] = min(vecMin[left], vecMin[right]);
        if (vecMin[left] == vecMin[right]) {
            vecCnt[id] = vecCnt[left] + vecCnt[right];
        } else if (vecMin[left] < vecMin[right]) {
            vecCnt[id] = vecCnt[left];
        } else {
            vecCnt[id] = vecCnt[right];
        }
    }

    void pushAdd(int id, int v) {
        vecMin[id] += v;
        vecLazy[id] += v;
    }

    void pushDown(int id) {
        int left = id * 2 + 1, right = id * 2 + 2;
        pushAdd(left, vecLazy[id]);
        pushAdd(right, vecLazy[id]);
        vecLazy[id] = 0;
    }

    void build(int id, int l, int r) {
        vecMin[id] = vecLazy[id] = 0;
        vecCnt[id] = r - l + 1;
        if (l == r) {
            return;
        }
        int m = (l + r) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        build(left, l, m);
        build(right, m + 1, r);
    }

    void update(int id, int l, int r, int i, int j, int v) {
        if (j < l || i > r) {
            return;
        }
        if (i <= l && r <= j) {
            vecMin[id] += v;
            vecLazy[id] += v;
            return;
        }
        pushDown(id);
        int m = (l + r) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        update(left, l, m, i, j, v);
        update(right, m + 1, r, i, j, v);
        mergeChild(id);
    }

    int query(int id, int l, int r, int i, int j) {
        if (j < l || i > r) {
            return 0;
        }
        if (i <= l && r <= j) {
            return vecMin[id] == 1 ? vecCnt[id] : 0;
        }
        pushDown(id);
        int m = (l + r) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        return query(left, l, m, i, j) + query(right, m + 1, r, i, j);
    }
};

int T, n;
vector <vector <int>> vecAdj;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void SolveTestCase() {
    cin >> n;
    vecAdj.clear();
    vecAdj.resize(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        vecAdj[u].push_back(v);
        vecAdj[v].push_back(u);
    }
    segmenttree stA(n);
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        stA.update(0, 1, n, 1, i, 1);
        for (auto j : vecAdj[i]) {
            if (j < i) {
                stA.update(0, 1, n, 1, j, - 1);
            }
        }
        ans += (ll)stA.query(0, 1, n, 1, i);
    }
    cout << ans << "\n";
}

void Solve() {
    cin >> T;
    while (T--) {
        SolveTestCase();
    }
}

int main() {
    Task();
    Solve();
}
