#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    int x, y;

    Point() {}
    Point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator < (Point p) {
        return x != p.x ? x < p.x : y < p.y;
    }

    Point operator + (Point p) {
        return Point(x + p.x, y + p.y);
    }

    Point operator - (Point p) {
        return Point(x - p.x, y - p.y);
    }

    Point operator * (int k) {
        return Point(x * k, y * k);
    }

    ll cross(Point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    ll dot(Point p) {
        return (ll)x * p.x + (ll)y * p.y;
    }

    int ccw(Point pa, Point pb) {
        ll c = (pa - *this).cross(pb - *this);
        return !c ? 0 : (c > 0 ? 1 : - 1);
    }

    bool on(Point pa, Point pb) {
        return !ccw(pa, pb) && (pa - *this).dot(pb - *this) <= 0;
    }

    bool inSP(vector <Point> &vecP) {
        int n = vecP.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int iNext = (i + 1) % n;
            Point pa = vecP[i], pb = vecP[iNext];
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

    bool inCP(vector <Point> &vecP) {
        int n = vecP.size();
        if (on(vecP[0], vecP[1]) || on(vecP[0], vecP[n - 1])) {
            return true;
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
        vector <Point> vecP1 = {vecP[0], vecP[r - 1], vecP[r]};
        return inSP(vecP1);
    }
};

int M1, M2, N;
vector <Point> vecP1, vecP2;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

vector <Point> Make_up(vector <Point> vecP) {
    vector <Point> vecAns;
    int n = vecP.size();
    for (int i = 0; i < n; ++i) {
        int iPrev = (i - 1 + n) % n, iNext = (i + 1) % n;
        if (vecP[iPrev].ccw(vecP[i], vecP[iNext])) {
            vecAns.push_back(vecP[i]);
        }
    }
    return vecAns;
}

vector <Point> Something(vector <Point> vecP, int k) {
    vector <Point> vecAns;
    int n = vecP.size();
    for (int i = 0; i < n; ++i) {
        vecAns.push_back(vecP[i] * k);
    }
    return vecAns;
}

vector <Point> Minkowski_Sum(vector <Point> vecP1, vector <Point> vecP2) {
    vector <Point> vecAns;
    int n1 = vecP1.size(), n2 = vecP2.size();
    int i1 = 0, i2 = 0;
    for (int i = 1; i < n1; ++i) {
        if (vecP1[i] < vecP1[i1]) {
            i1 = i;
        }
    }
    for (int i = 1; i < n2; ++i) {
        if (vecP2[i] < vecP2[i2]) {
            i2 = i;
        }
    }
    vecAns.push_back(vecP1[i1] + vecP2[i2]);
    for (int i = 1; i < n1 + n2; ++i) {
        int i1Next = (i1 + 1) % n1, i2Next = (i2 + 1) % n2;
        Point pa = vecP1[i1Next] + vecP2[i2], pb = vecP1[i1] + vecP2[i2Next], pc = vecAns.back();
        if (pc.ccw(pa, pb) > 0 || pb.on(pa, pc)) {
            vecAns.push_back(pa);
            i1 = i1Next;
        } else {
            vecAns.push_back(pb);
            i2 = i2Next;
        }
    }
    return Make_up(vecAns);
}

void Solve() {
    cin >> M1;
    vecP1.resize(M1);
    for (int i = 0; i < M1; ++i) {
        cin >> vecP1[i].x >> vecP1[i].y;
    }
    cin >> M2;
    vecP2.resize(M2);
    for (int i = 0; i < M2; ++i) {
        cin >> vecP2[i].x >> vecP2[i].y;
    }
    vector <vector <Point>> vecP(3);
    vecP[0] = Minkowski_Sum(vecP1, vecP2);
    vecP[1] = Minkowski_Sum(Something(vecP1, 2), Something(vecP2, - 1));
    vecP[2] = Minkowski_Sum(Something(vecP1, - 1), Something(vecP2, 2));
    cin >> N;
    while (N--) {
        Point p; cin >> p.x >> p.y;
        cout << ((p * 2).inCP(vecP[0]) || p.inCP(vecP[1]) || p.inCP(vecP[2]) ? "Y" : "N");
    }
}

int main() {
    Task();
    Solve();
}
