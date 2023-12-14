#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;
const ll INF = 1e9 + 9;

struct SegTree {
    vector <ll> sum, lazysum, lazymul, lazyvalue;

    SegTree() {}
    SegTree(int n) {
        sum.assign(n * 4, 0);
        lazysum.assign(n * 4, 0);
        lazymul.assign(n * 4, 1);
        lazyvalue.assign(n * 4, INF);
    }

    void pushAdd(int id, int l, int r, ll lzsum, ll lzmul, ll lzvalue) {
        if (lzvalue != INF) {
            sum[id] = lzvalue * (r - l + 1) % MOD;
            lazysum[id] = 0;
            lazymul[id] = 1;
            lazyvalue[id] = lzvalue;
        }
        sum[id] = (sum[id] * lzmul % MOD + lzsum * (r - l + 1) % MOD) % MOD;
        lazysum[id] = (lazysum[id] * lzmul % MOD + lzsum) % MOD;
        lazymul[id] = (lazymul[id] * lzmul) % MOD;
    }

    void pushDown(int id, int l, int r) {
        int m = (l + r) / 2;
        pushAdd(id * 2 + 1, l, m, lazysum[id], lazymul[id], lazyvalue[id]);
        pushAdd(id * 2 + 2, m + 1, r, lazysum[id], lazymul[id], lazyvalue[id]);
        lazysum[id] = 0;
        lazymul[id] = 1;
        lazyvalue[id] = INF;
    }

    void update1(int id, int l, int r, int from, int to, ll value) {
        if (from > r || to < l) {
            return;
        }
        if (from <= l && r <= to) {
            sum[id] = (sum[id] + value * (r - l + 1) % MOD) % MOD;
            lazysum[id] = (lazysum[id] + value) % MOD;
            return;
        }
        pushDown(id, l, r);
        int m = (l + r) / 2;
        update1(id * 2 + 1, l, m, from, to, value);
        update1(id * 2 + 2, m + 1, r, from, to, value);
        sum[id] = (sum[id * 2 + 1] + sum[id * 2 + 2]) % MOD;
    }

    void update2(int id, int l, int r, int from, int to, ll value) {
        if (from > r || to < l) {
            return;
        }
        if (from <= l && r <= to) {
            sum[id] = sum[id] * value % MOD;
            lazysum[id] = lazysum[id] * value % MOD;
            lazymul[id] = lazymul[id] * value % MOD;
            return;
        }
        pushDown(id, l, r);
        int m = (l + r) / 2;
        update2(id * 2 + 1, l, m, from, to, value);
        update2(id * 2 + 2, m + 1, r, from, to, value);
        sum[id] = (sum[id * 2 + 1] + sum[id * 2 + 2]) % MOD;
    }

    void update3(int id, int l, int r, int from, int to, ll value) {
        if (from > r || to < l) {
            return;
        }
        if (from <= l && r <= to) {
            sum[id] = value * (r - l + 1) % MOD;
            lazysum[id] = 0;
            lazymul[id] = 1;
            lazyvalue[id] = value;
            return;
        }
        pushDown(id, l, r);
        int m = (l + r) / 2;
        update3(id * 2 + 1, l, m, from, to, value);
        update3(id * 2 + 2, m + 1, r, from, to, value);
        sum[id] = (sum[id * 2 + 1] + sum[id * 2 + 2]) % MOD;
    }

    ll query(int id, int l, int r, int from, int to) {
        if (from > r || to < l) {
            return 0;
        }
        if (from <= l && r <= to) {
            return sum[id];
        }
        pushDown(id, l, r);
        int m = (l + r) / 2;
        return (query(id * 2 + 1, l, m, from, to) + query(id * 2 + 2, m + 1, r, from, to)) % MOD;
    }
};

void Task() {
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    int n, m; cin >> n >> m;

    SegTree ST(n);

    for (int i = 1; i <= n; ++i) {
        ll a; cin >> a;
        ST.update3(0, 1, n, i, i, a);
    }

    while (m--) {
        int t; cin >> t;

        if (t == 4) {
            int l, r; cin >> l >> r;

            ll ans = ST.query(0, 1, n, l, r);
            cout << ans << "\n";
        } else {
            int l, r; cin >> l >> r;
            ll x; cin >> x;

            if (t == 1) {
                ST.update1(0, 1, n, l, r, x);
            } else if (t == 2) {
                ST.update2(0, 1, n, l, r, x);
            } else {
                ST.update3(0, 1, n, l, r, x);
            }
        }
    }
}

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    Task();
    Solve();
}
