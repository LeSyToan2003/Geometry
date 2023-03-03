#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const int INF = 1e7;
const ld eps = 1e-9;

bool eq(ld a, ld b) {
    return abs(a - b) <= eps;
}

int sign(ld a) {
    return eq(a, 0) ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    ld x, y;

    point() {}
    point(ld x, ld y) {
        (*this).x = x;
        (*this).y = y;
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

struct line {
    point M, N;

    line() {}
    line(point M, point N) {
        (*this).M = M;
        (*this).N = N;
    }

    point dir() {
        return N - M;
    }

    bool contain(point p) {
        return M.ccw(N, p) > 0;
    }

    point pits(line l) {
        return M + dir() * (l.dir().cross(M - l.M) / dir().cross(l.dir()));
    }
};

int n;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

ld Area(vector <point> &p) {
    ld area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        area += p[i].cross(p[ii]);
    }
    return abs(area);
}

bool Check(int m) {
    deque <line> hp;
    deque <point> pts;
    for (int i = 0; i < n; ++i) {
        int ii = (i + m + 1) % n;
        line l = line(p[i], p[ii]);
        while (hp.size() > 1 && !l.contain(pts.back())) {
            hp.pop_back();
            pts.pop_back();
        }
        while (hp.size() > 1 && !l.contain(pts.front())) {
            hp.pop_front();
            pts.pop_front();
        }
        hp.push_back(l);
        if (hp.size() > 1) {
            pts.push_back(hp[hp.size() - 1].pits(hp[hp.size() - 2]));
        }
    }
    while (hp.size() > 2 && !hp.front().contain(pts.back())) {
        hp.pop_back();
        pts.pop_back();
    }
    while (hp.size() > 2 && !hp.back().contain(pts.front())) {
        hp.pop_front();
        pts.pop_front();
    }
    pts.push_back(hp.back().pits(hp.front()));
    vector <point> polygon = vector <point> (pts.begin(), pts.end());
    return !eq(Area(polygon), 0);
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    reverse(p.begin(), p.end());

    int l = 1, r = n - 2;
    while (l <= r) {
        int m = (l + r) / 2;
        if (Check(m)) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }

    cout << l;
}

int main() {
    Task();
    Solve();
}
