#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef double db;
typedef long double ld;

const ll mod = 1e9 + 7;
const db eps = 1e-9;
const db pi = acos(- 1);
tree <event, null_type, less<event>, rb_tree_tag, tree_order_statistics_node_update> Tree;

bool eq(db a, db b) { return abs(a - b) <= eps; }
bool lt(db a, db b) { return a < b - eps; }
bool gt(db a, db b) { return a > b + eps; }
bool leq(db a, db b) { return a <= b + eps; }
bool geq(db a, db b) { return a >= b - eps; }
int sign(db a) { return (eq(a, 0) ? 0 : (gt(a, 0) ? 1 : - 1)); }

struct point {
    // Coordinate
    db x, y;

    // Constructor
    point() {}
    point(db a, db b) { x = a, y = b; }

    // Overloading Function
    bool operator == (point p) { return eq(x, p.x) && eq(y, p.y); }
    bool operator != (point p) { return !eq(x, p.x) || !eq(y, p.y); }
    bool operator < (point p) { return lt(y, p.y) || (eq(y, p.y) && lt(x, p.x)); }
    bool operator > (point p) { return gt(x, p.x) || (eq(x, p.x) && gt(y, p.y)); }
    point operator + (point p) { return point(x + p.x, y + p.y); }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    point operator * (db k) { return point(x * k, y * k); }
    point operator / (db k) { return point(x / k, y / k); }
    db operator * (point p) { return x * p.x + y * p.y; }

    // Basic Function
    db norm() { return hypot(x, y); }
    db norm2() { return x * x + y * y; }
    point unit() { return point(x / norm(), y / norm()); }

    // Cross Product
    db det(point p) { return x * p.y - y * p.x; }

    // Distance
    db dist(point p) { return (p - *this).norm(); }
    db dist2(point p) { return (p - *this).norm2(); }

    // Return Angle of vector *this -> p
    db rad(point p) { return atan2(det(p), *this * p); }

    // Rotating 90 degree about the origin (0;0)
    point rot90() { return point(- y, x); }

    // Rotating about the origin (0;0)
    point rot(db angle) { return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)); }

    // Rotating about the point p
    point rot(point p, db angle) { return (*this - p).rot(angle) + p; }

    // Return: Projection of point in the line
    point proj(point pa, point pb) { return pa + (pb - pa) * ((pb - pa) * (*this - pa) / (pa - pb).norm2()); }

    // Return: Reflection of point through the line
    point refl(point pa, point pb) { point q = proj(pa, pb); return q + q - *this; }

    // Return: Distance from the point to the line
    db dist(point pa, point pb) { point q = proj(pa, pb); return dist(q); }

    // Return: Area of Triangle
    db area(point pa, point pb) { return abs((pa.x - x) * (pb.y - y) - (pa.y - y) * (pb.x - x)) / 2; }

    // Check: Three points are collinear(0) / counter clockwise(1) / clockwisse(-1)
    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }

    // Check: Point lies on the segment
    bool on(point pa, point pb) { return ccw(pa, pb) ? false : leq((pa - *this) * (pb - *this), 0); }

    // Check: Point is inside the simple polygon O(N)
    bool insp(vector <point> &p) {
        int n = p.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (on(p[i], p[ii])) { return true; }
            point u = p[i], v = p[ii];
            if (u.y < v.y) { swap(u, v); }
            if (gt(y, v.y) && leq(y, u.y) && ccw(u, v) < 0) { cnt ^= 1; }
        }
        return cnt;
    }

    // Check: Point is inside the convex polygon O(logN)
    bool incp(vector <point> &p) {
        int n = p.size();
        if (on(p[0], p[1]) || on(p[0], p[n - 1])) { return true; }
        int l = 2, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(p[0], p[m]) <= 0) { r = m; }
            else { l = m + 1; }
        }
        if (on(p[r - 1], p[r])) { return true; }
        vector <point> tri = {p[0], p[r - 1], p[r]};
        return insp(tri);
    }

    // Check: Point is outside(0) / inside(1) / on border(2) the circle
    bool inc(point p, db r) { db d = (*this - p).norm2(); return d == r * r ? 2 : (d < r * r ? 1 : 0); }
};

// Return Area of the simple polygon
db Area(vector <point> &p) {
    db area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        area += p[i].x * p[ii].y - p[i].y * p[ii].x;
    }
    return abs(area) / 2;
}

struct line {
    // Endpoints
    point M, N;

    // Constructor
    line() {}
    line(point pa, point pb) { M = pa, N = pb; }

    // Direction of the line
    point dir() { return N - M; }

    // Check: Two lines can intersect
    bool lits(line l) { return !eq(dir().det(l.dir()), 0); }

    // Check: Two segments can intersect
    bool its(line l) {
        if (M.on(l.M, l.N) || N.on(l.M, l.N) || l.M.on(M, N) || l.N.on(M, N)) { return true; }
        return M.ccw(l.M, l.N) != N.ccw(l.M, l.N) && l.M.ccw(M, N) != l.N.ccw(M, N);
    }

    // Return: Intersection of two lines
    point pits(line l) { M + dir() * (l.dir().det(M - l.M) / dir().det(l.dir())); }

    // Cut the simple polygon with counter-clockwise order
    vector <point> Cut(vector <point> &p) {
        vector <point> result;
        int n = p.size();
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (p[i].ccw(M, N) >= 0) { result.push_back(p[i]); }
            if (p[i].ccw(M, N) * p[ii].ccw(M, N) < 0) { result.push_back(pits(line(p[i], p[ii]))); }
        }
        if (eq(Area(result), 0)) { return {}; }
        return result;
    }

    // Cut the circle
    vector <point> Cut(point center, db r) {
        if (gt(center.dist(M, N), r)) { return {}; }
        point p = center.proj(M, N), u = (N - M).unit();
        db d = sqrt(max((db)0, r * r - (center - p).norm2()));
        return {p - u * d, p + u * d};
    }
};

struct circle {
    // Center I and Radius r
    point I;
    db r;

    // Constructor
    circle() {}
    circle(point p, db a) { I = p, r = a; }

    // Check: This circle contains that circle
    bool contain(circle c) { return leq((I - c.I).norm() + c.r, r); }

    // Check: Two circles can intersect
    bool its(circle c) { db d = (I - c.I).norm2(); return (r - c.r) * (r - c.r) <= d && d <= (r + c.r) * (r + c.r); }

    // Return: Intersections of two circles
    vector <point> pits(circle c) {
        db d = (I - c.I).norm(), l = (r * r - c.r * c.r + d * d) / (d * 2.0), h = sqrt(abs(r * r - l * l));
        db x1 = l / d * (c.I.x - I.x) + h / d * (c.I.y - I.y) + I.x, y1 = l / d * (c.I.y - I.y) - h / d * (c.I.x - I.x) + I.y;
        db x2 = l / d * (c.I.x - I.x) - h / d * (c.I.y - I.y) + I.x, y2 = l / d * (c.I.y - I.y) + h / d * (c.I.x - I.x) + I.y;
        return {point(x1, y1), point(x2, y2)};
    }
};

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {

}

int main() {
    Task();
    Solve();
}
