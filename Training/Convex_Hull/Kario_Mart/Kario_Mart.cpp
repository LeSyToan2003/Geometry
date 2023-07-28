#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int sign(int a) {
    return !a ? 0 : a > 0 ? 1 : - 1;
}

struct point {
    int x, y;
    bool status;

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

    ld norm() {
        return hypot(x, y);
    }

    int dot(point p) {
        return x * p.x + y * p.y;
    }

    int cross(point p) {
        return x * p.y - y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }

    bool on(point pa, point pb) {
        return !ccw(pa, pb) && (pa - *this).dot(pb - *this) <= 0;
    }

    bool inSimplePolygon(vector <point> &vecP) {
        int n = vecP.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            point pa = vecP[i], pb = vecP[ii];
            if (on(pa, pb)) {
                return false;
            }
            if (pa.y > pb.y) {
                swap(pa, pb);
            }
            if (pa.y <= y && y < pb.y && ccw(pa, pb) < 0) {
                cnt++;
            }
        }
        return cnt % 2;
    }
};

int n, m;
vector <point> vecP1, vecP2;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void ConvexHull(vector <point> &vecP) {
    int n = vecP.size();
    if (n < 3) {
        return;
    }
    sort(vecP.begin(), vecP.end());
    vector <point> vecPinit = vecP;
    int nNew = 0;
    vecP.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || vecPinit[0].ccw(vecPinit[i], vecPinit[n - 1]) > 0) {
            while (nNew > 0 && vecP[nNew - 1].ccw(vecP[nNew], vecPinit[i]) <= 0) {
                nNew--;
            }
            vecP[++nNew] = vecPinit[i];
        }
    }
    for (int i = n - 2, j = nNew; i >= 0; --i) {
        if (!i || vecPinit[n - 1].ccw(vecPinit[i], vecPinit[0]) > 0) {
            while (nNew > j && vecP[nNew - 1].ccw(vecP[nNew], vecPinit[i]) <= 0) {
                nNew--;
            }
            vecP[++nNew] = vecPinit[i];
        }
    }
    vecP.resize(nNew);
}

void Solve() {
    cin >> n >> m;
    vecP1.resize(n), vecP2.resize(m);
    for (int i = 0; i < n; ++i) {
        cin >> vecP1[i].x >> vecP1[i].y;
        vecP1[i].status = true;
    }
    for (int i = 0; i < m; ++i) {
        cin >> vecP2[i].x >> vecP2[i].y;
    }
    bool chk = true;
    while (chk) {
        chk = false;
        vector <point> vecP0;
        for (int i = 0; i < n; ++i) {
            vecP0.push_back(vecP1[i]);
            if (!vecP1[i].status) continue;
            int iPre = (i - 1 + n) % n, iNxt = (i + 1) % n;
            if (vecP1[iPre].ccw(vecP1[i], vecP1[iNxt]) < 0) continue;
            vector <point> vecP3 = {vecP1[iPre], vecP1[i], vecP1[iNxt]}, vecP4 = {vecP1[iPre], vecP1[iNxt]};
            for (auto p : vecP2) {
                if (!p.inSimplePolygon(vecP3)) continue;
                vecP4.push_back(p);
            }
            chk = true;
            ConvexHull(vecP4);
            vecP0.pop_back();
            int nP4 = vecP4.size(), k;
            for (k = 0; k < nP4 && vecP4[k] != vecP1[iPre]; ++k);
            while (vecP4[(k + 1) % nP4] != vecP1[iNxt]) {
                vecP0.push_back(vecP4[(k + 1) % nP4]);
                vecP0.back().status = false;
                k = (k + 1) % nP4;
            }
            for (int j = i + 1; j < n; ++j) {
                vecP0.push_back(vecP1[j]);
            }
            break;
        }
        vecP1 = vecP0;
        n = vecP1.size();
    }
    ld ans = 0;
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        ans += (vecP1[i] - vecP1[ii]).norm();
    }
    cout << fixed << setprecision(10) << ans;
}

int main() {
    Task();
    Solve();
}
