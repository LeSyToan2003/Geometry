#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

struct segmenttree {
    vector <ll> vecMin, vecMinCnt, vecLazy;

    segmenttree() {}
    segmenttree(int n) {
        vecMin.resize(n * 4), vecMinCnt.resize(n * 4), vecLazy.resize(n * 4);
        build(0, 1, n);
    }

    void build(int id, int l, int r) {
        vecMin[id] = vecLazy[id] = 0;
        vecMinCnt[id] = r - l + 1;
        if (l == r) {
            return;
        }
        int m = (l + r) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        build(left, l, m);
        build(right, m + 1, r);
    }

    void mergeChild(int id) {
        int left = id * 2 + 1, right = id * 2 + 2;
        vecMin[id] = min(vecMin[left], vecMin[right]);
        if (vecMin[left] == vecMin[right]) {
            vecMinCnt[id] = vecMinCnt[left] + vecMinCnt[right];
        } else if (vecMin[left] < vecMin[right]) {
            vecMinCnt[id] = vecMinCnt[left];
        } else {
            vecMinCnt[id] = vecMinCnt[right];
        }
    }

    void pushAdd(int id, ll v) {
        vecMin[id] += v;
        vecLazy[id] += v;
    }

    void pushDown(int id) {
        int left = id * 2 + 1, right = id * 2 + 2;
        pushAdd(left, vecLazy[id]);
        pushAdd(right, vecLazy[id]);
        vecLazy[id] = 0;
    }

    void update(int id, int l, int r, int i, int j, ll v) {
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
    segmenttree stA = segmenttree(n);
    for (int i = 1; i <= n; ++i) {
        stA.update(0, 1, n, 1, n - i + 1, - i);
    }
    for (int i = 1; i <= n; ++i) {
        stA.update(0, 1, n, 1, i, vecA[i]);
    }
    while (q--) {
        int i, j;
        cin >> i >> j;
        stA.update(0, 1, n, 1, i, vecA[j] - vecA[i]);
        stA.update(0, 1, n, 1, j, vecA[i] - vecA[j]);
        swap(vecA[i], vecA[j]);
        int ans = stA.vecMinCnt[0];
        cout << ans << "\n";
    }
}

int main() {
    Task();
    Solve();
}
