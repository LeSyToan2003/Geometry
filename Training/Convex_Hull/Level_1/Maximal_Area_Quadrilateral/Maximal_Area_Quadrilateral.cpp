#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int sign(int a) {
    return !a ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator != (point p) {
        return x != p.x || y != p.y;
    }

    bool operator < (point p) {
        return y != p.y ? y < p.y : x < p.x;
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

    int area(point pa, point pb) {
        return abs((pa - *this).cross(pb - *this));
    }
};

int n, maxx;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

vector <point> Build_ConvexHull(vector <point> &vecP) {
    sort(vecP.begin(), vecP.end());
    vector <point> vecPts = vecP;
    int n = vecP.size(), sz = 0;
    vecP.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || vecPts[0].ccw(vecPts[i], vecPts[n - 1]) > 0) {
            while (sz > 0 && vecP[sz - 1].ccw(vecP[sz], vecPts[i]) <= 0) {
                sz--;
            }
            vecP[++sz] = vecPts[i];
        }
    }
    for (int i = n - 2, j = sz; i >= 0; --i) {
        if (i == 0 || vecPts[n - 1].ccw(vecPts[i], vecPts[0]) > 0) {
            while (sz > j && vecP[sz - 1].ccw(vecP[sz], vecPts[i]) <= 0) {
                sz--;
            }
            vecP[++sz] = vecPts[i];
        }
    }
    vecP.resize(sz);
    return vecP;
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    vector <point> vecPts = vecP;
    vecP = Build_ConvexHull(vecP);
    int n = vecP.size();
    if (n < 4) {
        int minn = 1e9;
        for (auto p : vecPts) {
            if (p != vecP[0] && p != vecP[1] && p != vecP[2]) {
                minn = min(minn, p.area(vecP[0], vecP[1]));
                minn = min(minn, p.area(vecP[0], vecP[2]));
                minn = min(minn, p.area(vecP[1], vecP[2]));
            }
        }
        maxx = vecP[0].area(vecP[1], vecP[2]) - minn;
    } else {
        for (int i = 0; i < n; ++i) {
            int it1 = (i + 1) % n, it2 = (i + 3) % n, ii = (i + 2) % n;
            while ((it2 + 1) % n != i && vecP[i].area(vecP[ii], vecP[(it2 + 1) % n]) > vecP[i].area(vecP[ii], vecP[it2])) {
                it2 = (it2 + 1) % n;
            }
            maxx = max(maxx, vecP[i].area(vecP[ii], vecP[it1]) + vecP[i].area(vecP[ii], vecP[it2]));
            for (int j = (i + 3) % n; j != (i - 1 + n) % n; j = (j + 1) % n) {
                while ((it1 + 1) % n != j && vecP[i].area(vecP[j], vecP[(it1 + 1) % n]) > vecP[i].area(vecP[j], vecP[it1])) {
                    it1 = (it1 + 1) % n;
                }
                while ((it2 + 1) % n != i && vecP[i].area(vecP[j], vecP[(it2 + 1) % n]) > vecP[i].area(vecP[j], vecP[it2])) {
                    it2 = (it2 + 1) % n;
                }
                maxx = max(maxx, vecP[i].area(vecP[j], vecP[it1]) + vecP[i].area(vecP[j], vecP[it2]));
            }
        }
    }
    cout << fixed << setprecision(1) << (ld)maxx / 2;
}

int main() {
    Task();
    Solve();
}
