// Problem: http://oj.husc.edu.vn/

#include <bits/stdc++.h>

using namespace std;

typedef double db;

const db eps = 1e-9;

bool eq(db a, db b) { return abs(a - b) <= eps; }
bool gt(db a, db b) { return a > b + eps; }
int sign(db a) { return (eq(a, 0) ? 0 : (gt(a, 0) ? 1 : - 1)); }

struct point {
    db x, y;

    point() {}
    point(db a, db b) { x = a, y = b; }

    point operator + (point p) { return point(x + p.x, y + p.y); }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    point operator * (db k) { return point(x * k, y * k); }
    db operator * (point p) { return x * p.x + y * p.y; }

    db det(point p) { return x * p.y - y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

db Area(vector <point> &p) {
    db area = 0;
    for (int i = 0; i < p.size(); ++i) {
        int nxt = (i + 1) % p.size();
        area += p[i].x * p[nxt].y - p[i].y * p[nxt].x;
    }
    return area;
}

struct line {
    point M, N;

    line() {};
    line(point a, point b) { M = a, N = b; }

    point dir() { return N - M; }

    point its(line l) { return M + dir() * (l.dir().det(M - l.M) / dir().det(l.dir())); }

    vector <point> Cut(vector <point> &p) {
        vector <point> pts;
        int n = p.size();
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (p[i].ccw(M, N) >= 0) {
                pts.push_back(p[i]);
            }
            if (p[i].ccw(M, N) * p[ii].ccw(M, N) < 0) {
                pts.push_back(its(line(p[i], p[ii])));
            }
        }
        if (eq(Area(pts), 0)) { return {}; }
        return pts;
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

db Check(db x) {
    vector <vector <point>> polygon(2);
    polygon[0] = line(point(x, 1), point(x, 2)).Cut(p);
    polygon[1] = line(point(x, 2), point(x, 1)).Cut(p);
    return Area(polygon[1]) - Area(polygon[0]);
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    if (Area(p) < 0) {
        reverse(p.begin(), p.end());
    }

    db l = 1e18, r = 0;
    for (int i = 0; i < n; ++i) {
        l = min(l, p[i].x);
        r = max(r, p[i].x);
    }
    int loop = 0;
    while (++loop <= 100) {
        db m = (l + r) / 2;
        db curr = Check(m);
        if (eq(curr, 0)) {
            return void(cout << fixed << setprecision(4) << m);
        }
        else if (curr > 0) {
            l = m;
        }
        else {
            r = m;
        }
    }

    cout << fixed << setprecision(4) << r;
}

int main() {
    Task();
    Solve();
}
