#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct point {
    int x, y;
};

struct line {
    point M, N;

    line() {}
    line(point _M, point _N) {
        M = _M, N = _N;
    }

    ld its(ld x) {
        return (x * (N.y - M.y) + 1.0 * M.y * (N.x - M.x) - 1.0 * M.x * (N.y - M.y)) / (N.x - M.x);
    }
};

int n, w, h;
ll cnt;
ld x;
vector <point> vecPoly;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (line la, line lb) {
    return la.its(x) < lb.its(x);
}

void Solve() {
    cin >> n >> w >> h;
    vecPoly.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecPoly[i].x >> vecPoly[i].y;
    }
    for (x = 0.5; x < w; ++x) {
        vector <line> vecL;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (min(vecPoly[i].x, vecPoly[ii].x) < x && max(vecPoly[i].x, vecPoly[ii].x) > x) {
                vecL.push_back(line(vecPoly[i], vecPoly[ii]));
            }
        }
        if (!vecL.empty()) {
            sort(vecL.begin(), vecL.end());
            int preY = 0;
            for (int i = 0; i + 1 < vecL.size(); i += 2) {
                int leftY = max((int)min(vecL[i].its(x - 0.5), vecL[i].its(x + 0.5)), preY);
                int rightY = ceil(max(vecL[i + 1].its(x - 0.5), vecL[i + 1].its(x + 0.5)));
                cnt += 1LL * (rightY - leftY);
                preY = rightY;
            }
        }
    }
    cout << cnt;
}

int main() {
    Task();
    Solve();
}
