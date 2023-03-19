#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld INF = 1e3 + 9;
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
    ld x;
    ld y;

    point() {}
    point(ld x, ld y) {
        (*this).x = x;
        (*this).y = y;
    }

    bool operator < (point p) {
        return y != p.y ? y < p.y : x < p.x;
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

    point operator / (ld k) {
        return point(x / k, y / k);
    }

    ld norm() {
        return hypot(x, y);
    }

    ld norm2() {
        return x * x + y * y;
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

    point proj(point pa, point pb) {
        return pa + (pb - pa) * ((pa - pb).dot(pa - *this) / (pa - pb).norm2());
    }

    point refl(point pa, point pb) {
        return proj(pa, pb) * 2 - *this;
    }

    bool insp(vector <point> &p) {
        int cnt = 0;
        int n = p.size();
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (on(p[i], p[ii])) {
                return true;
            }
            point pa = p[i];
            point pb = p[ii];
            if (pb.y < pa.y) {
                swap(pa, pb);
            }
            if (lt(pa.y, y) && leq(y, pb.y) && ccw(pa, pb) < 0) {
                cnt++;
            }
        }
        return cnt % 2;
    }
};

struct line {
    point M;
    point N;

    line() {}
    line(point M, point N) {
        (*this).M = M;
        (*this).N = N;
    }

    point dir() {
        return N - M;
    }

    bool sits(line l) {
        if (M.on(l.M, l.N) || N.on(l.M, l.N) || l.M.on(M, N) || l.N.on(M, N)) {
            return true;
        }
        return M.ccw(l.M, l.N) != N.ccw(l.M, l.N) && l.M.ccw(M, N) != l.N.ccw(M, N);
    }

    bool lits(line l) {
        return !eq(dir().cross(l.dir()), 0);
    }

    point its(line l) {
        return M + dir() * (l.dir().cross(M - l.M) / dir().cross(l.dir()));
    }

    vector <point> Cut(vector <point> p) {
        vector <point> res;
        int n = p.size();
        for (int i = 0; i < n; ++i) {
            if (p[i].ccw(M, N) <= 0) {
                res.push_back(p[i]);
            }
            int ii = (i + 1) % n;
            if (p[i].ccw(M, N) * p[ii].ccw(M, N) < 0) {
                res.push_back(its(line(p[i], p[ii])));
            }
        }
        return res;
    }
};

int n;
ld area;
point pa;
point pb;
vector <point> p;
vector <point> p1;
vector <point> p2;

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
    return area / 2;
}

vector <point> ConvexHull(vector <point> p) {
    vector <point> res;
    sort(p.begin(), p.end());
    res = p;
    if (p.size() >= 3) {
        int n = p.size();
        int sz = 0;
        res.resize(n + 1);
        for (int i = 1; i < n; ++i) {
            if (i == n - 1 || p[0].ccw(p[i], p[n - 1]) > 0) {
                while (sz > 0 && res[sz - 1].ccw(res[sz], p[i]) <= 0) {
                    sz--;
                }
                res[++sz] = p[i];
            }
        }
        for (int i = n - 2, j = sz; i >= 0; --i) {
            if (i == 0 || p[n - 1].ccw(p[i], p[0]) > 0) {
                while (sz > j && res[sz - 1].ccw(res[sz], p[i]) <= 0) {
                    sz--;
                }
                res[++sz] = p[i];
            }
        }
        res.resize(sz);
    }
    return res;
}

vector <point> Intersection(vector <point> p1, vector <point> p2) {
    vector <point> res;
    int n = p1.size();
    int m = p2.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        line li = line(p1[i], p1[ii]);
        for (int j = 0; j < m; ++j) {
            int jj = (j + 1) % m;
            line lj = line(p2[j], p2[jj]);
            if (li.lits(lj) && li.sits(lj)) {
                res.push_back(li.its(lj));
            }
        }
    }
    for (auto p : p1) {
        if (p.insp(p2)) {
            res.push_back(p);
        }
    }
    for (auto p : p2) {
        if (p.insp(p1)) {
            res.push_back(p);
        }
    }
    res = ConvexHull(res);
    return res;
}

ld Area_of_Intersection(vector <point> p1, vector <point> p2) {
    ld area = 0;
    if (lt(Area(p1), 0)) {
        reverse(p1.begin(), p1.end());
    }
    if (lt(Area(p2), 0)) {
        reverse(p2.begin(), p2.end());
    }
    int n = p1.size();
    int m = p2.size();
    point pa = point(- INF, - INF);
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        for (int j = 0; j < m; ++j) {
            int jj = (j + 1) % m;
            if (pa.ccw(p1[i], p1[ii]) && pa.ccw(p2[j], p2[jj])) {
                vector <point> t1 = {pa, p1[i], p1[ii]};
                vector <point> t2 = {pa, p2[j], p2[jj]};
                vector <point> p = Intersection(t1, t2);
                area += Area(p) * sign(Area(t1)) * sign(Area(t2));
            }
        }
    }
    area = abs(area);
    return area;
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    cin >> pa.x >> pa.y >> pb.x >> pb.y;

    p1 = line(pa, pb).Cut(p);
    p2 = line(pb, pa).Cut(p);
    if (eq(Area(p1), 0) || eq(Area(p2), 0)) {
        return void(cout << 0);
    }

    for (int i = 0; i < p1.size(); ++i) {
        p1[i] = p1[i].refl(pa, pb);
    }

    area = Area_of_Intersection(p1, p2);

    cout << fixed << setprecision(10) << area;
}

int main() {
    Task();
    Solve();
}
