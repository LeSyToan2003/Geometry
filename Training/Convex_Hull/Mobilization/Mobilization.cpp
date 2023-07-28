
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld eps = 1e-9;

bool eq(ld a, ld b) {
    return abs(a - b) <= eps;
}

int sign(ld a) {
    return eq(a, 0) ? 0 : a > 0 ? 1 : - 1;
}

struct point {
    ld x, y;

    point() {}
    point(ld _x, ld _y) {
        x = _x, y = _y;
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

    ld cross(point p) {
        return x * p.y - y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }
};

int n, C;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void ConvexHull(vector <point> &vecP) {
    if (vecP.size() < 3) {
        return;
    }
    sort(vecP.begin(), vecP.end());
    int n = vecP.size(), nNew = 0;
    bool chk = true;
    for (int i = 2; i < n; ++i) {
        if (vecP[0].ccw(vecP[1], vecP[i])) {
            chk = false;
            break;
        }
    }
    if (chk) {
        vecP[1] = vecP[n - 1];
        vecP.resize(2);
        return;
    }
    vector <point> vecP1 = vecP;
    vecP.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || vecP1[0].ccw(vecP1[i], vecP1[n - 1]) > 0) {
            while (nNew > 0 && vecP[nNew - 1].ccw(vecP[nNew], vecP1[i]) <= 0) {
                nNew--;
            }
            vecP[++nNew] = vecP1[i];
        }
    }
    for (int i = n - 2, j = nNew; i >= 0; --i) {
        if (i == 0 || vecP1[n - 1].ccw(vecP1[i], vecP1[0]) > 0) {
            while (nNew > 0 && vecP[nNew - 1].ccw(vecP[nNew], vecP1[i]) <= 0) {
                nNew--;
            }
            vecP[++nNew] = vecP1[i];
        }
    }
    vecP.resize(nNew);
}

void Solve() {
    cin >> n >> C;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c >> vecP[i].x >> vecP[i].y;
        vecP[i].x *= (ld)C / c, vecP[i].y *= (ld)C / c;
    }
    ConvexHull(vecP);
    int n = vecP.size();
    ld ans = 0;
    for (int i = 0; i < n; ++i) {
        int ii = (i + 1) % n;
        if (vecP[i].x < vecP[ii].x && vecP[i].y < vecP[ii].y) {
            ans = max(ans, vecP[ii].x * vecP[ii].y);
        } else if (vecP[ii].x < vecP[i].x && vecP[ii].y < vecP[i].y) {
            ans = max(ans, vecP[i].x * vecP[i].y);
        } else {
            point p = vecP[ii] - vecP[i];
            ld l = 0, r = 1;
            for (int loop = 0; loop <= 100; ++loop) {
                ld m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
                point p1 = vecP[i] + p * m1, p2 = vecP[i] + p * m2;
                if (p1.x * p1.y > p2.x * p2.y) {
                    r = m2;
                } else {
                    l = m1;
                }
            }
            p = vecP[i] + p * l;
            ans = max(ans, p.x * p.y);
        }
    }
    cout << fixed << setprecision(2) << ans;
}

int main() {
    Task();
    Solve();
}
