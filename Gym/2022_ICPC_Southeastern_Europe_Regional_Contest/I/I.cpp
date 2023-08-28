#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct dsu {
    vector <int> vecParent, vecSize;

    dsu() {}
    dsu(int n) {
        vecParent.assign(n + 1, 0), vecSize.assign(n + 1, 1);
    }

    int findParent(int u) {
        return u == vecParent[u] ? u : vecParent[u] = findParent(vecParent[u]);
    }

    void unionSet(int u, int v) {
        int a = findParent(u), b = findParent(v);
        if (a == b) {
            return;
        }
        if (vecSize[a] < vecSize[b]) {
            swap(a, b);
        }
        vecSize[a] += vecSize[b];
        vecParent[b] = a;
    }
};

int n;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

int Ceil(int a, int b) {
    return (a + b - 1) / b;
}

void Solve() {
    cin >> n;
    vector <pair <int, int>> vecA(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        vecA[i] = {a, i};
    }
    sort(vecA.begin() + 1, vecA.end(), greater <pair <int, int>> ());
    dsu DSU(n);
    ll ans = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int pos = vecA[i].second;
        DSU.vecParent[pos] = pos;
        cnt++;
        if (pos > 1 && DSU.vecParent[pos - 1]) {
            int a = DSU.findParent(pos - 1), b = DSU.findParent(pos);
            cnt += 1LL* (Ceil(DSU.vecSize[a] + DSU.vecSize[b], 2) - Ceil(DSU.vecSize[a], 2) - Ceil(DSU.vecSize[b], 2));
            DSU.unionSet(a, b);
        }
        if (pos < n && DSU.vecParent[pos + 1]) {
            int a = DSU.findParent(pos + 1), b = DSU.findParent(pos);
            cnt += 1LL* (Ceil(DSU.vecSize[a] + DSU.vecSize[b], 2) - Ceil(DSU.vecSize[a], 2) - Ceil(DSU.vecSize[b], 2));
            DSU.unionSet(a, b);
        }
        if (i == n) {
            ans += cnt * vecA[i].first;
        } else {
            ans += cnt * (vecA[i].first - vecA[i + 1].first);
        }
    }
    cout << ans;
}

int main() {
    Task();
    Solve();
}
