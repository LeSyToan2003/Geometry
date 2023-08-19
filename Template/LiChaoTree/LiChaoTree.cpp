#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXX = 1e9;
const ll INF = 9e18;

struct query {
    int t, p;
    ll a, b;

    query() {}
    query(int _t, ll _a, ll _b, int _p) {
        t = _t, a = _a, b = _b, p = _p;
    }
};

struct line {
    ll a, b;

    line() {}
    line(ll _a, ll _b) {
        a = _a, b = _b;
    }

    ll getY(int x) {
        return a * x + b;
    }
};

struct lichaotree {
    int n;
    vector <int> vecX;
    vector <line> vecL;

    lichaotree() {}
    lichaotree(vector <int> _vecX) {
        vecX = _vecX;
        n = 1 << (int)ceil(log2(vecX.size()));
        while (vecX.size() < n) {
            vecX.push_back(MAXX);
        }
        vecL.assign(n * 4, line(0, INF));
    }

    void update(line li) {
        update(1, 0, n - 1, li);
    }

    void update(int id, int l, int r, line li) {
        int m = (l + r) / 2, x = vecX[m];
        if (li.getY(x) < vecL[id].getY(x)) {
            swap(vecL[id], li);
        }
        if (l == r) {
            return;
        }
        int left = id * 2, right = id * 2 + 1;
        if (li.a > vecL[id].a) {
            update(left, l, m, li);
        } else if (li.a < vecL[id].a) {
            update(right, m + 1, r, li);
        }
    }

    ll query(int x) {
        int id = lower_bound(vecX.begin(), vecX.end(), x) - vecX.begin() + n;
        ll ans = INF;
        while (id >= 1) {
            ans = min(ans, vecL[id].getY(x));
            id /= 2;
        }
        return ans;
    }
};

int n, q;
vector <line> vecL;
vector <query> vecQuery;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n >> q;
    vecL.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> vecL[i].a >> vecL[i].b;
    }
    vecQuery.resize(q + 1);
    vector <int> vecX;
    for (int i = 1; i <= q; ++i) {
        int t;
        cin >> t;
        if (!t) {
            ll a, b;
            cin >> a >> b;
            vecQuery[i] = query(t, a, b, 0);
        } else {
            int p;
            cin >> p;
            vecQuery[i] = query(t, 0, 0, p);
            vecX.push_back(p);
        }
    }
    sort(vecX.begin(), vecX.end());
    vecX.erase(unique(vecX.begin(), vecX.end()), vecX.end());
    lichaotree lctA(vecX);
    for (int i = 1; i <= n; ++i) {
        lctA.update(vecL[i]);
    }
    for (int i = 1; i <= q; ++i) {
        query query = vecQuery[i];
        if (!query.t) {
            lctA.update(line(query.a, query.b));
        } else {
            ll ans = lctA.query(query.p);
            cout << ans << "\n";
        }
    }
}

int main() {
    Task();
    Solve();
}
