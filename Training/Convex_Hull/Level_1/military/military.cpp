#include <bits/stdc++.h>

using namespace std;

int sign(int a) {
    return a == 0 ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y, index;
    bool joined;

    point() {}
    point(int x, int y) {
        (*this).x = x;
        (*this).y = y;
    }

    bool operator < (point a) {
        return y != a.y ? y < a.y : x < a.x;
    }
    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    int cross(point p) {
        return x * p.y - y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }
};

int n, cnt;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

vector <point> Build_ConvexHull(vector <point> &p) {
    sort(p.begin(), p.end());
    vector <point> res;
    int n = p.size();
    bool chk = true;
    for (int i = 2; i < n; ++i) {
        if (p[0].ccw(p[1], p[i])) {
            chk = false;
            break;
        }
    }
    if (chk) {
        p[1] = p.back();
        p.resize(2);
        res = p;
        p.clear();
        return res;
    }
    for (int i = 0; i < n; ++i) {
        p[i].index = i;
        p[i].joined = false;
    }
    vector <point> pts = p;
    p.resize(n + 1);
    int sz = 0;
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || pts[0].ccw(pts[i], pts[n - 1]) >= 0) {
            while (sz > 0 && p[sz - 1].ccw(p[sz], pts[i]) < 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    if (sz != n - 1) {
        for (int i = n - 2, j = sz; i >= 0; --i) {
            if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) >= 0) {
                while (sz > j && p[sz - 1].ccw(p[sz], pts[i]) < 0) {
                    sz--;
                }
                p[++sz] = pts[i];
            }
        }
        p.resize(sz);
    }
    else {
        p.resize(sz + 1);
    }
    res = p;
    for (int i = 0; i < p.size(); ++i) {
        pts[p[i].index].joined = true;
    }
    p.clear();
    for (int i = 0; i < n; ++i) {
        if (!pts[i].joined) {
            p.push_back(pts[i]);
        }
    }
    return res;
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    while (p.size() > 2) {
        vector <point> pts = Build_ConvexHull(p);
        if (pts.size() > 2) {
            cnt++;
        }
    }

    cout << cnt;
}

int main() {
    Task();
    Solve();
}
