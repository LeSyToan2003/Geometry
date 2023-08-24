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

    point operator + (point p) {
        return point(x + p.x, y + p.y);
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    point operator * (int k) {
        return point(x * k, y * k);
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
        return !ccw(pa, pb) && (pa - *this).dot(pb - *this) <= 0;
    }

    bool inSimplePolygon(vector <point> &vecP) {
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
            if (pa.y <= y && y < pb.y && ccw(pa, pb) < 0) {
                cnt++;
            }
        }
        return cnt % 2;
    }

    bool inConvexPolygon(vector <point> &vecP) {
        int n = vecP.size();
        if (on(vecP[0], vecP[1]) || on(vecP[0], vecP[n - 1])) {
            return true;
        }
        int l = 2, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(vecP[0], vecP[m]) < 0) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        vector <point> vecP1 = {vecP[0], vecP[l - 1], vecP[l]};
        return inSimplePolygon(vecP1);
    }
};

int m1, m2, n;
vector <point> vecP1, vecP2;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

vector <point> Translation (vector <point> &vecP, int k) {
    vector <point> vecAns;
    for (auto p : vecP) {
        vecAns.push_back(p * k);
    }
    return vecAns;
}

vector <point> Squeez(vector <point> vecP) {
    int n = vecP.size();
    vector <point> vecAns;
    for (int i = 0; i < n; ++i) {
        int iPre = (i - 1 + n) % n, iNext = (i + 1) % n;
        if (vecP[iPre].ccw(vecP[i], vecP[iNext])) {
            vecAns.push_back(vecP[i]);
        }
    }
    return vecAns;
}

vector <point> Minkowski(vector <point> vecP1, vector <point> vecP2) {
    int n1 = vecP1.size(), n2 = vecP2.size(), i1 = 0, i2 = 0;
    for (int i = 1; i < n1; ++i) {
        if (vecP1[i].x < vecP1[i1].x || (vecP1[i].x == vecP1[i1].x && vecP1[i].y < vecP1[i1].y)) {
            i1 = i;
        }
    }
    for (int i = 1; i < n2; ++i) {
        if (vecP2[i].x < vecP2[i2].x || (vecP2[i].x == vecP2[i2].x && vecP2[i].y < vecP2[i2].y)) {
            i2 = i;
        }
    }
    vector <point> vecAns = {vecP1[i1] + vecP2[i2]};
    for (int i = 1; i < n1 + n2; ++i) {
        point p1 = vecP1[(i1 + 1) % n1] + vecP2[i2], p2 = vecP1[i1] + vecP2[(i2 + 1) % n2];
        if (vecAns.back().ccw(p1, p2) > 0 || p2.on(vecAns.back(), p1)) {
            vecAns.push_back(p1);
            i1 = (i1 + 1) % n1;
        } else {
            vecAns.push_back(p2);
            i2 = (i2 + 1) % n2;
        }
    }
    return Squeez(vecAns);
}

void Solve() {
    cin >> m1;
    vecP1.resize(m1);
    for (int i = 0; i < m1; ++i) {
        cin >> vecP1[i].x >> vecP1[i].y;
    }
    cin >> m2;
    vecP2.resize(m2);
    for (int i = 0; i < m2; ++i) {
        cin >> vecP2[i].x >> vecP2[i].y;
    }
    vector <point> vecP3 = Minkowski(vecP1, vecP2);
    vector <point> vecP4 = Minkowski(Translation(vecP1, 2), Translation(vecP2, - 1));
    vector <point> vecP5 = Minkowski(Translation(vecP1, - 1), Translation(vecP2, 2));
    cin >> n;
    while (n--) {
        point p;
        cin >> p.x >> p.y;
        cout << ((p * 2).inConvexPolygon(vecP3) || p.inConvexPolygon(vecP4) || p.inConvexPolygon(vecP5) ? "Y" : "N");
    }
}


int main() {
    Task();
    Solve();
}
