#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld eps = 1e-6;

bool eq(ld a, ld b) {
    return abs(a - b) <= eps;
}

int sign(ld a) {
    return eq(a, 0) ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    ld x, y;

    point() {}
    point(ld _x, ld _y) {
        x = _x, y = _y;
    }

    point operator + (point p) {
        return point(x + p.x, y + p.y);
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    point operator * (ld k) {
        return point(x * k, y * k);
    }

    ld cross(point p) {
        return x * p.y - y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }
};

struct halfplane {
    point M, N;

    halfplane() {}
    halfplane(point _M, point _N) {
        M = _M, N = _N;
    }

    point dir() {
        return N - M;
    }

    bool contain(point p) {
        return p.ccw(M, N) <= 0;
    }

    point its(halfplane hp) {
        return M + dir() * (hp.dir().cross(M - hp.M) / dir().cross(hp.dir()));
    }
};

int n;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

ld Area(vector <point> p) {
    ld area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        area += p[i].cross(p[ii]);
    }
    return abs(area);
}

bool Check(int m) {
    deque <halfplane> dqHp;
    deque <point> dqP;
    for (int i = 0; i < n; ++i) {
        int ii = (i + m + 1) % n;
        halfplane hp(vecP[i], vecP[ii]);
        while (!dqP.empty() && !hp.contain(dqP.back())) {
            dqHp.pop_back();
            dqP.pop_back();
        }
        while (!dqP.empty() && !hp.contain(dqP.front())) {
            dqHp.pop_front();
            dqP.pop_front();
        }
        if (!dqHp.empty()) {
            dqP.push_back(hp.its(dqHp.back()));
        }
        dqHp.push_back(hp);
    }
    while (dqHp.size() > 2 && !dqHp.front().contain(dqP.back())) {
        dqHp.pop_back();
        dqP.pop_back();
    }
    while (dqHp.size() > 2 && !dqHp.back().contain(dqP.front())) {
        dqHp.pop_front();
        dqP.pop_front();
    }
    dqP.push_back(dqHp.back().its(dqHp.front()));
    vector <point> vecPoly(dqP.begin(), dqP.end());
    return !eq(Area(vecPoly), 0);
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    int l = 1, r = n - 2;
    while (l < r) {
        int m = (l + r) / 2;
        if (Check(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    cout << l;
}

int main() {
    Task();
    Solve();
}
