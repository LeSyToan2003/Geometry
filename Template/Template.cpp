#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;

const ll mod = 1e9 + 7;
const ld INF = 1e9 + 9;
const ld eps = 1e-9;
const ld pi = acos(- 1);
tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Tree;

bool eq(ld a, ld b) {
    return abs(a - b) <= eps;
}

bool lt(ld a, ld b) {
    return a < b - eps;
}

bool gt(ld a, ld b) {
    return a > b + eps;
}

bool leq(ld a, ld b) {
    return a <= b + eps;
}

bool geq(ld a, ld b) {
    return a >= b - eps;
}

int sign(ld a) {
    return (eq(a, 0) ? 0 : (gt(a, 0) ? 1 : - 1));
}

struct point {
    // Coordinate
    ld x, y;

    // Constructor
    point() {}
    point(ld a, ld b) {
        x = a;
        y = b;
    }

    bool operator == (point p) {
        return eq(x, p.x) && eq(y, p.y);
    }

    bool operator != (point p) {
        return !eq(x, p.x) || !eq(y, p.y);
    }

    bool operator < (point p) {
        return !eq(y, p.y) ? lt(y, p.y) : lt(x, p.x);
    }

    bool operator > (point p) {
        return !eq(y, p.y) ? gt(y, p.y) : gt(x, p.x);
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

    // Length of a vector
    ld norm() {
        return hypot(x, y);
    }

    // Square of the length of a vector
    ld norm2() {
        return x * x + y * y;
    }

    // Unit vector
    point unit() {
        return point(x / norm(), y / norm());
    }

    // Dot product
    ld dot(point p) {
        return x * p.x + y * p.y;
    }

    // Cross Product
    ld cross(point p) {
        return x * p.y - y * p.x;
    }

    // Rotating about origin O(0;0)
    point rot(ld angle) {
        return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }

    // Rotating about a point p
    point rot(point p, ld angle) {
        return (*this - p).rot(angle) + p;
    }

    // Projection of a point onto a line
    point proj(point pa, point pb) {
        return pa + (pb - pa) * ((pa - pb).dot(pa - *this) / (pa - pb).norm2());
    }

    // Reflection of a point over a line
    point refl(point pa, point pb) {
        return proj(pa, pb) * 2 - *this;
    }

    //Distance from a point to a segment
    ld sdist(point pa, point pb) {
        ld res;
        ld a = (pa - *this).norm2();
        ld b = (pb - *this).norm2();
        ld c = (pa - pb).norm2();
        if (a > b + c) {
            res = sqrt(b);
        }
        else if (b > a + c) {
            res = sqrt(a);
        }
        else {
            res = area(pa, pb) / sqrt(c);
        }
        return res;
    }

    // Distance from a point to a line
    ld ldist(point pa, point pb) {
        return (proj(pa, pb) - *this).norm();
    }

    // Area of Triangle
    ld area(point pa, point pb) {
        return abs((pa - *this).cross(pb - *this)) / 2;
    }

    // Orientation of three points
    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }

    // A point lies on a segment
    bool on(point pa, point pb) {
        return ccw(pa, pb) ? false : leq((pa - *this).dot(pb - *this), 0);
    }

    // A point lies inside or outside a simple polygon - O(N)
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

    // A point lies inside or outside a convex polygon - O(logN)
    bool incp(vector <point> &p) {
        int n = p.size();
        if (on(p[0], p[1]) || on(p[0], p[n - 1])) {
            return true;
        }
        int l = 2;
        int r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(p[0], p[m]) <= 0) {
                r = m;
            }
            else {
                l = m + 1;
            }
        }
        if (on(p[r - 1], p[r])) {
            return true;
        }
        vector <point> tri = {p[0], p[r - 1], p[r]};
        return insp(tri);
    }

    // A point lies inside or outside a circle
    bool inc(point p, ld r) {
        return (p - *this).norm2() <= r * r;
    }
};

struct line {
    // Endpoints
    point M, N;

    // Constructor
    line() {}
    line(point M, point N) {
        (*this).M = M;
        (*this).N = N;
    }

    // Direction of a line
    point dir() {
        return N - M;
    }

    // Two lines can intersect
    bool lits(line l) {
        return !eq(dir().cross(l.dir()), 0);
    }

    // Two segments can intersect
    bool sits(line l) {
        if (M.on(l.M, l.N) || N.on(l.M, l.N) || l.M.on(M, N) || l.N.on(M, N)) {
            return true;
        }
        return M.ccw(l.M, l.N) != N.ccw(l.M, l.N) && l.M.ccw(M, N) != l.N.ccw(M, N);
    }

    // Intersection of two lines
    point its(line l) {
        return M + dir() * (l.dir().cross(M - l.M) / dir().cross(l.dir()));
    }

    // Cut a simple polygon
    vector <point> Cut(vector <point> &p) {
        vector <point> res;
        int n = p.size();
        for (int i = 0; i < n; ++i) {
            if (p[i].ccw(M, N) >= 0) {
                res.push_back(p[i]);
            }
            int ii = (i + 1) % n;
            if (p[i].ccw(M, N) * p[ii].ccw(M, N) < 0) {
                res.push_back(its(line(p[i], p[ii])));
            }
        }
        return res;
    }

    // Cut the circle
    vector <point> Cut(point center, ld r) {
        vector <point> res;
        if (leq(center.ldist(M, N), r)) {
            point p = center.proj(M, N);
            point u = (N - M).unit();
            ld l = (center - p).norm2();
            ld d = sqrt(max((ld)0, r * r - l));
            res = {p - u * d, p + u * d};
        }
        return res;
    }
};

struct circle {
    // Center I and Radius r
    point I;
    ld r;

    // Constructor
    circle() {}
    circle(point p, ld a) {
        I = p, r = a;
    }

    // Check: Circle contains other circle
    bool contain(circle c) {
        return leq((I - c.I).norm() + c.r, r);
    }

    // Check: Two circles can intersect
    bool cits(circle c) {
        ld d = (I - c.I).norm2();
        return (r - c.r) * (r - c.r) <= d && d <= (r + c.r) * (r + c.r);
    }

    // Return: Intersections of two circles
    vector <point> its(circle c) {
        vector <point> res;
        ld d = (I - c.I).norm();
        ld l = (r * r - c.r * c.r + d * d) / (d * 2.0);
        ld h = sqrt(abs(r * r - l * l));
        point p1 = I + (point(l * (c.I.x - I.x) + h * (c.I.y - I.y), l * (c.I.y - I.y) - h * (c.I.x - I.x))) / d;
        point p2 = I + (point(l * (c.I.x - I.x) - h * (c.I.y - I.y), l * (c.I.y - I.y) + h * (c.I.x - I.x))) / d;
        res = {p1, p2};
        return res;
    }
};

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

// Convexhull - O(NlogN)
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

// Area of a simple polygon - O(N)
ld Area(vector <point> &p) {
    ld area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        area += p[i].cross(p[ii]);
    }
    return abs(area) / 2;
}

// Intersection of two convex polygons - O(N^2)
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

// Area of the intersection of two simple polygons - O(N^2)
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

}

int main() {
    Task();
    Solve();
}
