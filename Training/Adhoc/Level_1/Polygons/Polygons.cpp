#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) {
    return !a ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll dot(point p) {
        return (ll)x * p.x + (ll)y * p.y;
    }

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }

    bool on(point pa, point pb) {
        return ccw(pa, pb) ? false : (pa - *this).dot(pb - *this) <= 0;
    }

    bool insp(vector <point> &vecP) {
        int n = vecP.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            point pa = vecP[i], pb = vecP[ii];
            if (on(pa, pb)) {
                return true;
            }
            if (pa.y > pb.y) {
                swap(pa, pb);
            }
            if (pa.y < y && y <= pb.y && ccw(pa, pb) < 0) {
                cnt++;
            }
        }
        return cnt % 2 == 1;
    }

    bool incp(vector <point> &vecP) {
        int n = vecP.size();
        if (on(vecP[0], vecP[1]) || on(vecP[0], vecP[n - 1])) {
            return false;
        }
        int l = 2, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(vecP[0], vecP[m]) <= 0) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        if (on(vecP[r - 1], vecP[r])) {
            return false;
        }
        vector <point> vecPts = {vecP[0], vecP[r - 1], vecP[r]};
        return insp(vecPts);
    }
};

int n, m;
vector <point> vecPa, vecPb;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    vecPa.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecPa[i].x >> vecPa[i].y;
    }
    reverse(vecPa.begin(), vecPa.end());
    cin >> m;
    vecPb.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> vecPb[i].x >> vecPb[i].y;
    }
    bool chk = true;
    for (auto p : vecPb) {
        if (!p.incp(vecPa)) {
            chk = false;
            break;
        }
    }
    cout << (chk ? "YES" : "NO");
}

int main() {
    Task();
    Solve();
}
