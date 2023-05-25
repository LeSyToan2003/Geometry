#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct square {
    ll x, y, l;
};

struct its {
    ll s, l, r, b, t;

    its() {}
    its(ll _s, ll _l, ll _r, ll _b, ll _t) {
        s = _s;
        l = max(min(_l, s), 0LL), r = max(min(_r, s), 0LL);
        b = max(min(_b, s), 0LL), t = max(min(_t, s), 0LL);
        if (l == r || b == t) {
            l = r = b = t = 0;
        } else if (l == 0 && r == s && b == 0 && t == s) {
            s = l = r = b = t = 0;
        } else if (l == 0 && r == s) {
            t -= b;
            b = 0;
        } else if (b == 0 && t == s) {
            r -= l;
            l = 0;
        }
    }

    bool operator == (its i) {
        return s == i.s && l == i.l && r == i.r && b == i.b && t == i.t;
    }
};

int n;
vector <square> vecR;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("squares.in", "r", stdin);
    freopen("squares.out", "w", stdout);
}

bool operator < (its ia, its ib) {
    if (ia.s != ib.s) {
        return ia.s < ib.s;
    }
    if (ia.l != ib.l) {
        return ia.l < ib.l;
    }
    if (ia.r != ib.r) {
        return ia.r < ib.r;
    }
    if (ia.b != ib.b) {
        return ia.b < ib.b;
    }
    return ia.t < ib.t;
}

its Intersection(square sa, square sb) {
    return its(sa.l, sb.x - sa.x, sb.x - sa.x + sb.l, sb.y - sa.y, sb.y - sa.y + sb.l);
}

void Solve() {
    cin >> n;
    vecR.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecR[i].x >> vecR[i].y >> vecR[i].l;
    }
    ll cnt = 0;
    map <its, int> mapIts;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                mapIts[Intersection(vecR[i], vecR[j])]++;
            }
        }
    }
    for (auto i : mapIts) {
        cnt += (ll)i.second * (i.second - 1);
    }
    for (int i = 0; i < n; ++i) {
        map <its, int> mapItsA, mapItsB;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                mapItsA[Intersection(vecR[i], vecR[j])]++;
                mapItsB[Intersection(vecR[j], vecR[i])]++;
            }
        }
        for (auto j : mapItsA) {
            cnt -= (ll)j.second * (j.second - 1);
        }
        for (auto j : mapItsB) {
            cnt -= (ll)j.second * (j.second - 1);
        }
        for (auto j : mapItsA) {
            cnt -= (ll)j.second * mapItsB[j.first] * 2;
        }
    }
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (Intersection(vecR[i], vecR[j]) == Intersection(vecR[j], vecR[i])) {
                cnt += 2LL;
            }
        }
    }
    cout << cnt;
}

int main() {
    Task();
    Solve();
}
