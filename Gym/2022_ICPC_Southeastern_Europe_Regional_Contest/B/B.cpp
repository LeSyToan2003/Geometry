#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct Point {
    int x, y;

    Point() {}
    Point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator < (Point p) {
        return upper() != p.upper() ? upper() < p.upper() : cross(p) < 0;
    }

    Point operator + (Point p) {
        return Point(x + p.x, y + p.y);
    }

    Point operator - (Point p) {
        return Point(x - p.x, y - p.y);
    }

    bool upper() {
        return y > 0 || (!y && x < 0);
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
};

int n, m;
vector <Point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool cmp(int i, int j) {
    return vecP[i] < vecP[j];
}

void Solve() {
    cin >> n >> m;
    vecP.resize(n + m);
    for (int i = 0; i < n + m; ++i) {
        ld x, y; cin >> x >> y;
        x *= 1e6, y *= 1e6;
        vecP[i] = Point(x, y);
    }
    int ans = 0;
    for (int i = n; i < n + m; ++i) {
        vector <int> vecA;
        for (int j = 0; j < n + m; ++j) {
            if (j != i) {
                vecP[j] = vecP[j] - vecP[i];
                vecA.push_back(j);
            }
        }
        sort(vecA.begin(), vecA.end(), cmp);
        int nA = vecA.size();
        vector <int> vecCnt(2, 0);
        int idx = 0;
        vecCnt[vecA[idx] >= n]++;
        for (int j = 0; j < nA; ++j) {
            while (true) {
                int idxNext = (idx + 1) % nA;
                Point pa = vecP[vecA[j]], pb = vecP[vecA[idxNext]], pc = Point(0, 0);
                if (idxNext != j && (pa.on(pb, pc) || pb.on(pa, pc) || pc.ccw(pa, pb) < 0)) {
                    idx = idxNext;
                    vecCnt[vecA[idx] >= n]++;
                } else {
                    break;
                }
            }
            if (!vecCnt[1]) {
                ans = max(ans, vecCnt[0]);
            }
            if (idx == j) {
                idx = (idx + 1) % nA;
                vecCnt[vecA[idx] >= n]++;
            }
            vecCnt[vecA[j] >= n]--;
        }
        for (int j = 0; j < n + m; ++j) {
            if (j != i) {
                vecP[j] = vecP[j] + vecP[i];
            }
        }
    }
    cout << ans;
}

int main() {
    Task();
    Solve();
}
