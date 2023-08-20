#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 9e18;

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

struct query {
    int t, x;
    line l;
};

struct lichaotree {
    vector <int> vecX;
    vector <line> vecL;

    lichaotree() {}
    lichaotree(vector <int> _vecX) {
        vecX = _vecX;
        int n = vecX.size();
        vecL.assign(n * 4, line(0, INF));
    }

    void update(int id, int l, int r, line li) {
        if (l == r) {
            if (li.getY(vecX[l]) < vecL[id].getY(vecX[l])) {
                vecL[id] = li;
            }
            return;
        }
        if (li.a < vecL[id].a) {
            swap(li, vecL[id]);
        }
        int m = (l + r) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if (li.getY(vecX[m]) > vecL[id].getY(vecX[m])) {
            update(left, l, m, li);
        } else {
            swap(li, vecL[id]);
            update(right, m + 1, r, li);
        }
    }

    ll query(int id, int l, int r, int x) {
        ll ans = vecL[id].getY(x);
        if (l == r) {
            return ans;
        }
        int m = (l + r) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if (x <= vecX[m]) {
            return min(ans, query(left, l, m, x));
        }
        return min(ans, query(right, m + 1, r, x));
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
        cin >> vecQuery[i].t;
        if (!vecQuery[i].t) {
            cin >> vecQuery[i].l.a >> vecQuery[i].l.b;
        } else {
            cin >> vecQuery[i].x;
            vecX.push_back(vecQuery[i].x);
        }
    }
    sort(vecX.begin(), vecX.end());
    vecX.erase(unique(vecX.begin(), vecX.end()), vecX.end());
    int nX = vecX.size();
    lichaotree lctA(vecX);
    for (int i = 1; i <= n; ++i) {
        lctA.update(0, 0, nX - 1, vecL[i]);
    }
    for (int i = 1; i <= q; ++i) {
        if (!vecQuery[i].t) {
            lctA.update(0, 0, nX - 1, vecQuery[i].l);
        } else {
            ll ans = lctA.query(0, 0, nX - 1, vecQuery[i].x);
            cout << ans << "\n";
        }
    }
}

int main() {
    Task();
    Solve();
}
