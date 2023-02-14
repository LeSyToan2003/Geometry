#include <bits/stdc++.h>

using namespace std;

typedef double db;
typedef long long ll;
typedef long double ld;

const ll mod = 1e9 + 7;
const ld eps = 1e-9;
const ld pi = acos(- 1);

bool eq(ld a, ld b) { return abs(a - b) <= eps; }
bool lt(ld a, ld b) { return !eq(a, b) && a < b; }
bool gt(ld a, ld b) { return !eq(a, b) && a > b; }
bool le(ld a, ld b) { return eq(a, b) || a < b; }
bool ge(ld a, ld b) { return eq(a, b) || a > b; }
int sign(ld a) { return (eq(a, 0) ? 0 : (gt(a, 0) ? 1 : - 1)); }

// Point
struct point {
    ld x, y;

    // Constructor
    point() {}
    point(ld a, ld b) { x = a, y = b; }

    // Overloading Function
    bool operator == (point p) { return eq(x, p.x) && eq(y, p.y); }
    bool operator != (point p) { return !eq(x, p.x) || !eq(y, p.y); }
    bool operator < (point p) { return lt(y, p.y) || (eq(y, p.y) && lt(x, p.x)); }
    bool operator > (point p) { return gt(x, p.x) || (eq(x, p.x) && gt(y, p.y)); }
    point operator + (point p) { return point(x + p.x, y + p.y); }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    point operator * (ld k) { return point(x * k, y * k); }
    point operator / (ld k) { return point(x / k, y / k); }
    ld operator * (point p) { return x * p.x + y * p.y; }

    // Basic Function
    ld norm() { return hypot(x, y); }
    ld norm2() { return x * x + y * y; }
    point unit() { ld z = norm(); return point(x / z, y / z); }

    // Return ... with a point
    ld det(point p) { return x * p.y - y * p.x; }
    ld dist(point p) { return (p - *this).norm(); }
    ld dist2(point p) { return (p - *this).norm2(); }
    // Return Angle of vector *this -> p
    ld rad(point p) { return atan2(det(p), (*this) * p); }
    // Rotating 90 degree about the origin
    point rot90() { return point(- y, x); }
    // Rotating about the origin
    point rot(ld angle) { return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)); }
    // Rotating about the point
    point rot(point p, ld angle) { return (*this - p).rot(angle) + p; }
    // Return Projection of point in the line
    point proj(point pa, point pb) { return pa + (pb - pa) * ((pb - pa) * (*this - pa) / pa.dist2(pb)); }
    // Return Reflection of point through the line
    point refl(point pa, point pb) { point q = proj(pa, pb); return q + q - *this; }
    // Return Distance from the point to the line
    ld dist(point pa, point pb) { point q = proj(pa, pb); return dist(q); }

    //Return Area of Triangle (*this, pa, pb)
    ld area(point pa, point pb) { return abs((pa.x - x) * (pb.y - y) - (pa.y - y) * (pb.x - x)) / 2; }

    // Return (circle): 0(outside), 1(inside), 2(on border)
    bool inc(point p, ld r) { ld d = dist2(p); return d == r * r ? 2 : (d < r * r ? 1 : 0); }

    // Return: 0(collinear), 1(counter clockwise), - 1(clockwisse)
    int ccw(point pa, point pb) {
        ld c = (pa - *this).det(pb - *this);
        return sign(c);
    }

    // Return (line with endpoint: (pa, pb)): 0(not collinear), 1(between), 2(front), 3(back)
    int on(point pa, point pb) {
        if (ccw(pa, pb) != 0) { return 0; }
        if (le((*this - pa) * (*this - pb), 0)) { return 1; }
        return lt((pb - pa) * (*this - pa), 0) ? 3 : 2
    }

    // Return (simple polygon): 0(strictly outside), 1(strictly inside), 2(on border) in O(N)
    int inp1(vector <point> &p) {
        int n = p.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (on(p[i], p[ii]) == 1) { return 2; }
            point u = p[i], v = p[ii];
            if (u.y < v.y) {
                swap(u, v);
            }
            if (leq(y, v.y) || gt(y, u.y)) {
                continue;
            }
            if (u.ccw(*this, v) == 1) {
                cnt ^= 1;
            }
        }
        return cnt;
    }

    // Return (convex polygon with ccw order): 0(strictly outside), 1(strictly inside), 2(on border) in O(logN)
    int inp2(vector <point> &p) {
        int n = p.size();
        if (on(p[0], p[1]) == 1 || on(p[0], p[n - 1]) == 1) { return 2; }
        int l = 2, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(p[0], p[m]) > 0) {
                r = m;
            }
            else {
                l = m;
            }
        }
        if (on(p[r - 1], p[r]) == 1) { return 2; }
        vector <point> tri = {p[0], p[r - 1], p[r]};
        return inp1(tri) ? 1 : 0;
    }
};

// Return Area of the simple polygon
ld Area(vector <point> &p) {
    ld area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        area += p[i].x * p[ii].y - p[i].y * p[ii].x;
    }
    return abs(area) / 2;
}

// Line - Segment
struct line {
    point M, N;

    // Constructor
    line(point pa, point pb) {
        M = pa, N = pb;
    }

    // Direction of the line
    point dir() { return N - M; }

    // Check if segments strictly intersect
    bool its1(line l) {
        return M.ccw(l.M, l.N) * N.ccw(l.M, l.N) < 0 && l.M.ccw(M, N) * l.N.ccw(M, N) < 0;
    }
    // Check if segments intersect
    bool its2(line l) {
        if (M.on(l.M, l.N) == 1 || N.on(l.M, l.N) == 1 || l.M.on(M, N) == 1 || l.N.on(M, N) == 1) { return true; }
        return M.ccw(l.M, l.N) != N.ccw(l.M, l.N) && l.M.ccw(M, N) != l.N.ccw(M, N);
    }
    // Check if lines intersect
    bool its3(line l) {
        return !eq(dir().det(l.dir()), 0);
    }
    // Return Intersection of lines
    point its(line l) {
        M + dir() * (l.dir().det(M - l.M) / dir().det(l.dir()));
    }

    // Cut the simple polygon with ccw order
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

    // Cut the circle with center c and radius r
    vector <point> Cut(point c, ld r) {
        if (gt(c.dist(M, N), r)) { return {}; }
        point q = c.proj(M, N), u = (N - M).unit();
        ld d = sqrt(max((ld)0, r * r - c.dist2(q)));
        return {q - u * d, q + u * d};
    }
};

// Polygon
struct polygon {
    vector <point> pol, upp, dow, lef, rig;

    // Constructor
    polygon() {}
    polygon(vector <point> &p) { pol = p; }

    // Find Convexhull
    vector <point> convexhull() {
        vector <point> p = pol;
        sort(p.begin(), p.end());
        vector <point> pts = p;
        int n = p.size(), sz = 0;
        p.resize(n + 1);
        for (int i = 1; i < n; ++i) {
            if (i == n - 1 || pts[0].ccw(pts[i], pts[n - 1]) > 0) {
                while (sz > 0 && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
                    sz--;
                }
                p[++sz] = pts[i];
            }
        }
        for (int i = n - 2, j = sz; i >= 0; --i) {
            if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) > 0) {
                while (sz > j && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
                    sz--;
                }
                p[++sz] = pts[i];
            }
        }
        p.resize(sz);
        return p;
    }

    // Return Intersection of the convex polygons
    vector <point> its(polygon p) {
        vector <point> p1 = pol, p2 = p.pol;
        set <pair <ld, ld>> st;
        int n = p1.size(), m = p2.size();
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            for (int j = 0; j < m; ++j) {
                int jj = (j + 1) % m;
                line la = line(p1[i], p1[ii]), lb = line(p2[j], p2[jj]);
                if (!eq(la.dir().det(lb.dir()), 0) && la.its2(lb)) {
                    point P = la.its(lb);
                    st.insert({P.x, P.y});
                }
            }
        }
        for (auto it : p1) {
            if (it.inp2(p2)) {
                st.insert({it.x, it.y});
            }
        }
        for (auto it : p2) {
            if (it.inp2(p1)) {
                st.insert({it.x, it.y});
            }
        }
        vector <point> pts;
        for (auto it : st) {
            point P = point(it.first, it.second);
            if (pts.size() == 0 || !eq(pts.back().dist(P), 0)) {
                pts.push_back(P);
            }
        }
        polygon pp = polygon(pts);
        pp.convexhull();
        return pp.pol;
    }

    // Return Area of Intersection of the simple polygons
    ld areaits(polygon p) {
        vector <point> p1 = pol, p2 = p.pol;
        if (lt(Area(p1), 0)) { reverse(p1.begin(), p1.end()); }
        if (lt(Area(p2), 0)) { reverse(p2.begin(), p2.end()); }
        int n = p1.size(), m = p2.size();
        point P = point(- 1e9, - 1e9);
        ld area = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            for (int j = 0; j < m; ++j) {
                int jj = (j + 1) % m;
                if (P.ccw(p1[i], p1[ii]) != 0 && P.ccw(p2[j], p2[jj]) != 0) {
                    vector <point> tri1 = {P, p1[i], p1[ii]};
                    vector <point> tri2 = {P, p2[j], p2[jj]};
                    vector <point> pts = polygon(tri1).its(polygon(tri2));
                    area += sign(Area(tri1)) * sign(Area(tri2)) * Area(pts);
                }
            }
        }
        return abs(area);
    }
};

struct circle {
    point I;
    ld r;

    // Constructor
    circle() {}
    circle(point p, ld a) { I = p, r = a; }
};

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }


}
