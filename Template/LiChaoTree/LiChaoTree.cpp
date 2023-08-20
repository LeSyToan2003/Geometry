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

struct segment {
    int l, r;
    line li;
};

struct query {
    int t, x;
    segment s;
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

    void updateLine(int id, int l, int r, line li) {
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
            updateLine(left, l, m, li);
        } else {
            swap(li, vecL[id]);
            updateLine(right, m + 1, r, li);
        }
    }

    void updateSegment(int id, int l, int r, segment s) {
        if (l > r) {
            return;
        }
        if (s.r < vecX[l] || s.l > vecX[r]) {
            return;
        }
        if (s.l <= vecX[l] && vecX[r] <= s.r) {
            updateLine(id, l, r, s.li);
            return;
        }
        int m = (l + r) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        updateSegment(left, l, m, s);
        updateSegment(right, m + 1, r, s);
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
vector <segment> vecS;
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
    vecS.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> vecS[i].l >> vecS[i].r >> vecS[i].li.a >> vecS[i].li.b;
        vecS[i].r--;
    }
    vecQuery.resize(q + 1);
    vector <int> vecX;
    for (int i = 1; i <= q; ++i) {
        cin >> vecQuery[i].t;
        if (!vecQuery[i].t) {
            cin >> vecQuery[i].s.l >> vecQuery[i].s.r >> vecQuery[i].s.li.a >> vecQuery[i].s.li.b;
            vecQuery[i].s.r--;
        } else {
            cin >> vecQuery[i].x;
            vecX.push_back(vecQuery[i].x);
        }
    }
    sort(vecX.begin(), vecX.end());
    vecX.erase(unique(vecX.begin(), vecX.end()), vecX.end());
    int nX = vecX.size();
    lichaotree lctA = lichaotree(vecX);
    for (int i = 1; i <= n; ++i) {
        lctA.updateSegment(0, 0, nX - 1, vecS[i]);
    }
    for (int i = 1; i <= q; ++i) {
        if (!vecQuery[i].t) {
            lctA.updateSegment(0, 0, nX - 1, vecQuery[i].s);
        } else {
            ll ans = lctA.query(0, 0, nX - 1, vecQuery[i].x);
            if (ans != INF) {
                cout << ans << "\n";
            } else {
                cout << "INFINITY\n";
            }
        }
    }
}

int main() {
    Task();
    Solve();
}
