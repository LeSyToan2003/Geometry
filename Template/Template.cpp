#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;

const ll mod = 1e9 + 7;
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

    // Overloading Function
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

    // Basic Function
    ld norm() {
        return hypot(x, y);
    }
    ld norm2() {
        return x * x + y * y;
    }
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

    // Distance between two points
    ld dist(point p) {
        return (p - *this).norm();
    }
    ld dist2(point p) {
        return (p - *this).norm2();
    }

    // Return Angle of vector *this -> p
    ld rad(point p) {
        return atan2(cross(p), dot(p));
    }

    // Rotating 90 degree about the origin (0;0)
    point rot90() {
        return point(- y, x);
    }

    // Rotating about the origin (0;0)
    point rot(ld angle) {
        return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }

    // Rotating about the point p
    point rot(point p, ld angle) {
        return (*this - p).rot(angle) + p;
    }

    // Return: Projection of point in the line
    point proj(point pa, point pb) {
        return pa + (pb - pa) * ((pb - pa).dot(*this - pa) / (pa - pb).norm2());
    }

    // Return: Reflection of point through the line
    point refl(point pa, point pb) {
        return proj(pa, pb) * 2 - *this;
    }

    // Return: Distance from the point to the line
    ld dist(point pa, point pb) {
        point q = proj(pa, pb);
        return dist(q);
    }

    // Return: Area of Triangle
    ld area(point pa, point pb) {
        return abs((pa.x - x) * (pb.y - y) - (pa.y - y) * (pb.x - x)) / 2;
    }

    // Check: Three points are collinear(0) / counter clockwise(1) / clockwisse(-1)
    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }

    // Check: Point lies on the segment
    bool on(point pa, point pb) {
        return ccw(pa, pb) ? false : leq((pa - *this).dot(pb - *this), 0);
    }

    // Check: Point is inside the simple polygon O(N)
    bool insp(vector <point> &p) {
        int n = p.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (on(p[i], p[ii])) {
                return true;
            }
            point pa = p[i], pb = p[ii];
            if (pb.y < pa.y) {
                swap(pa, pb);
            }
            if (lt(pa.y, y) && leq(y, pb.y) && ccw(u, v) < 0) {
                cnt ^= 1;
            }
        }
        return cnt;
    }

    // Check: Point is inside the convex polygon O(logN)
    bool incp(vector <point> &p) {
        int n = p.size();
        if (on(p[0], p[1]) || on(p[0], p[n - 1])) {
            return true;
        }
        int l = 2, r = n - 1;
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

    // Check: Point is outside(0) / inside(1) / on border(2) the circle
    bool inc(point p, ld r) {
        ld d = (*this - p).norm2();
        return d == r * r ? 2 : (d < r * r ? 1 : 0);
    }
};

// Return Area of the simple polygon
ld Area(vector <point> &p) {
    ld area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        area += p[i].cross(p[ii]);
    }
    return abs(area) / 2;
}

struct line {
    // Endpoints
    point M, N;

    // Constructor
    line() {}
    line(point pa, point pb) {
        M = pa;
        N = pb;
    }

    // Direction of the line
    point dir() {
        return N - M;
    }

    // Check: Two lines can intersect
    bool lits(line l) {
        return !eq(dir().cross(l.dir()), 0);
    }

    // Check: Two segments can intersect
    bool its(line l) {
        if (M.on(l.M, l.N) || N.on(l.M, l.N) || l.M.on(M, N) || l.N.on(M, N)) {
            return true;
        }
        return M.ccw(l.M, l.N) != N.ccw(l.M, l.N) && l.M.ccw(M, N) != l.N.ccw(M, N);
    }

    // Return: Intersection of two lines
    point pits(line l) {
        return M + dir() * (l.dir().cross(M - l.M) / dir().cross(l.dir()));
    }

    // Cut the simple polygon with counter-clockwise order
    vector <point> Cut(vector <point> &p) {
        vector <point> result;
        int n = p.size();
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (p[i].ccw(M, N) >= 0) {
                result.push_back(p[i]);
            }
            if (p[i].ccw(M, N) * p[ii].ccw(M, N) < 0) {
                result.push_back(pits(line(p[i], p[ii])));
            }
        }
        if (eq(Area(result), 0)) {
            return {};
        }
        return result;
    }

    // Cut the circle
    vector <point> Cut(point center, ld r) {
        if (gt(center.dist(M, N), r)) {
            return {};
        }
        point p = center.proj(M, N);
        point u = (N - M).unit();
        ld d = sqrt(max((ld)0, r * r - (center - p).norm2()));
        return {p - u * d, p + u * d};
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
    bool its(circle c) {
        ld d = (I - c.I).norm2();
        return (r - c.r) * (r - c.r) <= d && d <= (r + c.r) * (r + c.r);
    }

    // Return: Intersections of two circles
    vector <point> pits(circle c) {
        ld d = (I - c.I).norm();
        ld l = (r * r - c.r * c.r + d * d) / (d * 2.0);
        ld h = sqrt(abs(r * r - l * l));
        ld x1 = l / d * (c.I.x - I.x) + h / d * (c.I.y - I.y) + I.x;
        ld y1 = l / d * (c.I.y - I.y) - h / d * (c.I.x - I.x) + I.y;
        ld x2 = l / d * (c.I.x - I.x) - h / d * (c.I.y - I.y) + I.x;
        ld y2 = l / d * (c.I.y - I.y) + h / d * (c.I.x - I.x) + I.y;
        vector <point> res = {point(x1, y1), point(x2, y2)};
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

void Solve() {

}

int main() {
    Task();
    Solve();
}
