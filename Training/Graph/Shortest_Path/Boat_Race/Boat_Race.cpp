#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ld eps = 1e-9;

bool eq(ld a, ld b) {
    return abs(a - b) <= eps;
}

bool lt(ld a, ld b) {
    return a < b - eps;
}

bool leq(ld a, ld b) {
    return a <= b + eps;
}

int sign(ld a) {
    return eq(a, 0) ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    ld x, y;
    bool st, en;

    point() {}
    point(ld _x, ld _y) {
        x = _x, y = _y;
    }

    bool operator == (point p) {
        return x == p.x && y == p.y;
    }

    point operator + (point p) {
        return point(x + p.x, y + p.y);
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    point operator / (ld k) {
        return point(x / k, y / k);
    }

    ld norm() {
        return hypot(x, y);
    }

    ld dot(point p) {
        return x * p.x + y * p.y;
    }

    ld cross(point p) {
        return x * p.y - y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }

    bool on(point pa, point pb) {
        return ccw(pa, pb) ? false : leq((pa - *this).dot(pb - *this), 0);
    }

    bool insp(vector <point> &vecP) {
        int n = vecP.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            point pa = vecP[i], pb = vecP[ii];
            if (on(pa, pb)) {
                return true;
            }
            if (pa.y > pb.y) {
                swap(pa, pb);
            }
            if (lt(pa.y, y) && leq(y, pb.y) && ccw(pa, pb) < 0) {
                cnt++;
            }
        }
        return cnt % 2 == 1;
    }
};

struct segment {
    point M, N;

    segment() {}
    segment(point _M, point _N) {
        M = _M, N = _N;
    }

    bool its(segment s) {
        if (M == s.M || M == s.N || N == s.M || N == s.N) {
            return false;
        }
        return M.ccw(s.M, s.N) != N.ccw(s.M, s.N) && s.M.ccw(M, N) != s.N.ccw(M, N);
    }
};

int n, w;
ld minn;
vector <point> vecP, vecPts;
vector <vector <ld>> path;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);
}

bool Go(point pa, point pb) {
    if (pa == pb) {
        return true;
    }
    point mid = (pa + pb) / 2;
    if (!mid.insp(vecPts)) {
        return false;
    }
    for (int i = 0; i + 1 < n; ++i) {
        if (segment(pa, pb).its(segment(vecP[i], vecP[i + 1]))) {
            return false;
        }
        if (segment(pa, pb).its(segment(vecP[i + n], vecP[i + n + 1]))) {
            return false;
        }
    }
    return true;
}

void Build() {
    path.resize(n * 2);
    for (int i = 0; i < n * 2; ++i) {
        path[i].assign(n * 2, 1e9);
        path[i][i] = 0;
    }
    for (int i = 0; i + 1 < n * 2; ++i) {
        for (int j = i + 1; j < n * 2; ++j) {
            if (Go(vecP[i], vecP[j])) {
                path[i][j] = path[j][i] = (vecP[i] - vecP[j]).norm();
            }
        }
    }
}

void Floyd() {
    for (int k = 0; k < n * 2; ++k) {
        for (int i = 0; i < n * 2; ++i) {
            for (int j = 0; j < n * 2; ++j) {
                path[i][j] = min(path[i][j], path[i][k] + path[k][j]);
            }
        }
    }
}

void Solve() {
    cin >> n;
    n++;
    vecP.resize(n * 2);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
        vecP[i].st = vecP[i].en = false;
        vecPts.push_back(vecP[i]);
    }
    cin >> w;
    for (int i = n; i < n * 2; ++i) {
        vecP[i] = point(vecP[i - n].x, vecP[i - n].y + w);
        vecP[i].st = vecP[i].en = false;
    }
    for (int i = n * 2 - 1; i >= n; --i) {
        vecPts.push_back(vecP[i]);
    }
    Build();
    Floyd();
    for (int i = 0; i < n * 2; ++i) {
        point pa = point(vecP[0].x, vecP[i].y), pb = point(vecP[n - 1].x, vecP[i].y);
        if (vecP[0].y <= vecP[i].y && vecP[i].y <= vecP[n].y && Go(pa, vecP[i])) {
            vecP[i].st = true;
        }
        if (vecP[n - 1].y <= vecP[i].y && vecP[i].y <= vecP[n * 2 - 1].y && Go(vecP[i], pb)) {
            vecP[i].en = true;
        }
    }
    minn = 1e9;
    for (int i = 0; i < n * 2; ++i) {
        for (int j = 0; j < n * 2; ++j) {
            if (vecP[i].st && vecP[j].en) {
                minn = min(minn, vecP[i].x - vecP[0].x + vecP[n - 1].x - vecP[j].x + path[i][j]);
            }
        }
    }
    cout << fixed << setprecision(10) << minn;
}

int main() {
    Task();
    Solve();
}
