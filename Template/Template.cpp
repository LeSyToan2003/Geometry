#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long double ld;
typedef tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update> orderedset;

const ld EPS = 1e-9;
const ld PI = acos(- 1);
const ld INF = 1e18;

bool eq(ld a, ld b) {
    return abs(a - b) <= EPS;
}

bool lt(ld a, ld b) {
    return a < b - EPS;
}

bool leq(ld a, ld b) {
    return a <= b + EPS;
}

struct Point {
    ld x, y;

    Point() {}
    Point(ld _x, ld _y) {
        x = _x, y = _y;
    }

    bool operator == (Point p) {
        return eq(x, p.x) && eq(y, p.y);
    }

    bool operator < (Point p) {
        return !eq(y, p.y) ? lt(y, p.y) : lt(x, p.x);
    }

    Point operator + (Point p) {
        return Point(x + p.x, y + p.y);
    }

    Point operator - (Point p) {
        return Point(x - p.x, y - p.y);
    }

    Point operator * (ld k) {
        return Point(x * k, y * k);
    }

    Point operator / (ld k) {
        return Point(x / k, y / k);
    }

    Point rotating(ld a) {
        return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    Point rotating(Point p, ld a) {
        return (*this - p).rotating(a) + p;
    }

    ld norm() {
        return hypot(x, y);
    }

    ld norm2() {
        return x * x + y * y;
    }

    ld dot(Point p) {
        return x * p.x + y * p.y;
    }

    ld cross(Point p) {
        return x * p.y - y * p.x;
    }

    ld area(Point pa, Point pb) {
        return abs((pa - *this).cross(pb - *this));
    }

    ld dist_line(Point pa, Point pb) {
        return area(pa, pb) / (pa - pb).norm();
    }

    ld dist_segment(Point pa, Point pb) {
        ld a = (pa - *this).norm(), b = (pb - *this).norm(), c = (pa - pb).norm();
        if (lt(a * a + c * c, b * b)) {
            return a;
        }
        if (lt(b * b + c * c, a * a)) {
            return b;
        }
        return area(pa, pb) / c;
    }

    int ccw(Point pa, Point pb) {
        ld c = (pa - *this).cross(pb - *this);
        return eq(c, 0) ? 0 : (c > 0 ? 1 : - 1);
    }

    bool on(Point pa, Point pb) {
        return !ccw(pa, pb) && leq((pa - *this).dot(pb - *this), 0);
    }

    Point projection(Point pa, Point pb) {
        ld a = (pa - *this).norm(), b = (pb - *this).norm(), c = (pa - pb).norm();
        ld h = area(pa, pb) / c, d = sqrt(a * a - h * h);
        if (lt(a * a + c * c, b * b)) {
            return (pa - pb) * (d + c) / c + pb;
        }
        return (pb - pa) * d / c + pa;
    }

    Point reflection(Point pa, Point pb) {
        return projection(pa, pb) * 2 - *this;
    }

    bool inSP(vector <Point> &vecP) {
        int n = vecP.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int iNext = (i + 1) % n;
            Point pa = vecP[i], pb = vecP[iNext];
            if (on(pa, pb)) {
                return true;
            }
            if (pa.y > pa.y) {
                swap(pa, pb);
            }
            if (leq(pa.y, y) && lt(y, pb.y) && ccw(pa, pb) < 0) {
                cnt++;
            }
        }
        return cnt % 2;
    }

    bool inCP(vector <Point> &vecP) {
        int n = vecP.size();
        if (on(vecP[0], vecP[1]) || on(vecP[0], vecP[n - 1])) {
            return true;
        }
        int l = 2, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(vecP[0], vecP[m]) <= 0) {
                r = m;
            }
            else {
                l = m + 1;
            }
        }
        if (on(vecP[r - 1], vecP[r])) {
            return true;
        }
        vector <Point> vecP1 = {vecP[0], vecP[r - 1], vecP[r]};
        return inSP(vecP1);
    }
};

struct Segment {
    Point M, N;

    Segment() {}
    Segment(Point _M, Point _N) {
        M = _M, N = _N;
    }

    bool is_its(Segment s) {
        if (M.on(s.M, s.N) || N.on(s.M, s.N) || s.M.on(M, N) || s.N.on(M, N)) {
            return true;
        }
        return M.ccw(s.M, s.N) != N.ccw(s.M, s.N) && s.M.ccw(M, N) != s.N.ccw(M, N);
    }

    Point its(Segment s) {
        return (N - M) * (s.N - s.M).cross(M - s.M) / (N - M).cross(s.N - s.M) + M;
    }

    vector <Point> cutP(vector <Point> &vecP) {
        vector <Point> vecAns;
        int n = vecP.size();
        for (int i = 0; i < n; ++i) {
            int iNext = (i + 1) % n;
            if (vecP[i].ccw(M, N) >= 0) {
                vecAns.push_back(vecP[i]);
            }
            if (vecP[i].ccw(M, N) * vecP[iNext].ccw(M, N) < 0) {
                vecAns.push_back(its(Segment(vecP[i], vecP[iNext])));
            }
        }
        return vecAns;
    }

    vector <Point> cutC(Point p, ld r) {
        vector <Point> vecAns;
        Point pa = p.projection(M, N), pb = (N - M) / (N - M).norm();
        ld h = (p - pa).norm(), d = sqrt(r * r - h * h);
        vecAns = {pa - pb * d, pa + pb * d};
        return vecAns;
    }
};

struct Circle {
    Point center;
    ld r;

    Circle() {}
    Circle(Point _center, ld _r) {
        center = _center, r = _r;
    }

    vector <Point> its(Circle c) {
        vector <Point> vecAns(2);
        ld d = (center - c.center).norm();
        ld a = acos((r * r + d * d - c.r * c.r) / (2 * r * d));
        ld l = r * cos(a), h = r * sin(a);
        Point pa = (c.center - center) * l / d + center, pb = (center - pa) * h / (center - pa).norm() + pa;
        vecAns[0] = pb.rotating(pa, PI / 2);
        vecAns[1] = pb.rotating(pa, - PI / 2);
        return vecAns;
    }
};

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

int sign(ld a) {
    return eq(a, 0) ? 0 : (a > 0 ? 1 : - 1);
}

ld Area(vector <Point> &vecP) {
    ld ans = 0;
    int n = vecP.size();
    for (int i = 0; i < n; ++i) {
        int iNext = (i + 1) % n;
        ans += vecP[i].cross(vecP[iNext]);
    }
    return ans / 2;
}

vector <Point> Convex_Hull(vector <Point> vecP) {
    sort(vecP.begin(), vecP.end());
    int n = vecP.size(), nAns = 0;
    if (n < 3) {
        return vecP;
    }
    vector <Point> vecAns = vecP;
    vecAns.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || vecP[0].ccw(vecP[i], vecP[n - 1]) > 0) {
            while (nAns && vecAns[nAns - 1].ccw(vecAns[nAns], vecP[i]) <= 0) {
                nAns--;
            }
            vecAns[++nAns] = vecP[i];
        }
    }
    for (int i = n - 2, j = nAns; i >= 0; --i) {
        if (!i || vecP[n - 1].ccw(vecP[i], vecP[0]) > 0) {
            while (nAns > j && vecAns[nAns - 1].ccw(vecAns[nAns], vecP[i]) <= 0) {
                nAns--;
            }
            vecAns[++nAns] = vecP[i];
        }
    }
    vecAns.resize(nAns);
    return vecAns;
}

vector <Point> Its_CP(vector <Point> vecP1, vector <Point> vecP2) {
    vector <Point> vecAns;
    int n1 = vecP1.size(), n2 = vecP2.size();
    for (int i = 0; i < n1; ++i) {
        int iNext = (i + 1) % n1;
        for (int j = 0; j < n2; ++j) {
            int jNext = (j + 1) % n2;
            Segment sa = Segment(vecP1[i], vecP1[iNext]), sb = Segment(vecP2[j], vecP2[jNext]);
            if (eq((sa.N - sa.M).cross(sb.N - sb.M), 0)) {
                continue;
            }
            if (!sa.is_its(sb)) {
                continue;
            }
            vecAns.push_back(sa.its(sb));
        }
    }
    for (auto p : vecP1) {
        if (p.inSP(vecP2)) {
            vecAns.push_back(p);
        }
    }
    for (auto p : vecP2) {
        if (p.inSP(vecP1)) {
            vecAns.push_back(p);
        }
    }
    vecAns = Convex_Hull(vecAns);
    return vecAns;
}

ld Its_SP(vector <Point> vecP1, vector <Point> vecP2) {
    ld ans = 0;
    if (lt(Area(vecP1), 0)) {
        reverse(vecP1.begin(), vecP1.end());
    }
    if (lt(Area(vecP2), 0)) {
        reverse(vecP2.begin(), vecP2.end());
    }
    int n1 = vecP1.size(), n2 = vecP2.size();
    Point p = Point(- INF, - INF);
    for (int i = 0; i < n1; ++i) {
        int iNext = (i + 1) % n1;
        for (int j = 0; j < n2; ++j) {
            int jNext = (j + 1) % n2;
            if (p.ccw(vecP1[i], vecP1[iNext]) && p.ccw(vecP2[j], vecP2[jNext])) {
                vector <Point> vecP3 = {p, vecP1[i], vecP1[iNext]};
                vector <Point> vecP4 = {p, vecP2[j], vecP2[jNext]};
                vector <Point> vecP5 = Its_CP(vecP3, vecP4);
                ans += Area(vecP5) * sign(Area(vecP3)) * sign(Area(vecP4));
            }
        }
    }
    return abs(ans);
}

void Solve() {

}

int main() {
    Task();
    Solve();
}
