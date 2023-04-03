#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ld pi = acos(- 1);

struct circle {
    int x, y, r;

    circle() {}
    circle(int _x, int _y, int _r) {
        x = _x, y = _y, r = _r;
    }

    bool contain(circle c) {
        return ((ll)x - (ll)c.x) * ((ll)x - (ll)c.x) + ((ll)y - (ll)c.y) * ((ll)y - (ll)c.y) <= (ll)r * r;
    }
};

struct event {
    int x, r, id, val;

    event() {}
    event(int _x, int _r, int _id, int _val) {
        x = _x, r = _r, id = _id, val = _val;
    }

    bool operator < (event e) {
        return x != e.x ? x < e.x : (val != e.val ? val < e.val : r > e.r);
    }
};

int n;
ld area;
vector <ld> vecA;
vector <circle> vecC;
set <circle> setC;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (circle a, circle b) {
    return a.y < b.y;
}

set <circle> :: iterator prev(set <circle> :: iterator it) {
    return it == setC.begin() ? setC.end() : --it;
}

void Solve() {
    cin >> n;
    vecC.resize(n);
    vecA.assign(n, 0);
    vector <event> vecE;
    for (int i = 0; i < n; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        vecC[i] = circle(x, y, r);
        vecA[i] = pi * r * r;
        vecE.push_back(event(x - r, r, i, 1));
        vecE.push_back(event(x + r, r, i, - 1));
    }
    sort(vecE.begin(), vecE.end());
    for (int i = 0; i < vecE.size(); ++i) {
        event e = vecE[i];
        circle c = vecC[e.id];
        if (e.val == 1) {
            bool chk = true;
            auto nxt = setC.lower_bound(c);
            auto pre = prev(nxt);
            circle cnxt = *nxt, cpre = *pre;
            if (nxt != setC.end() && cnxt.contain(c)) {
                chk = false;
            } else if (pre != setC.end() && cpre.contain(c)) {
                chk = false;
            }
            if (!chk) {
                vecA[e.id] = 0;
            } else {
                setC.insert(c);
            }
        } else if (vecA[e.id]) {
            setC.erase(c);
        }
    }
    area = accumulate(vecA.begin(), vecA.end(), 0.0);
    cout << fixed << setprecision(10) << area;
}

int main() {
    Task();
    Solve();
}
