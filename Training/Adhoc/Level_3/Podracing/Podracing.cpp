#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld eps = 1e-9;

bool leq(ld a, ld b) {
    return a <= b + eps;
}

struct point {
    int x, y;
};

struct segment {
    point M, N;

    segment() {}
    segment(point _M, point _N) {
        M = _M, N = _N;
    }

    ld its(ld y) {
        return (ld)M.x + ((ld)N.x - (ld)M.x) / ((ld)N.y - (ld)M.y) * (y - (ld)M.y);
    }
};

int n, m, q;
vector <point> vecLeft, vecRight, vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    vecLeft.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecLeft[i].x >> vecLeft[i].y;
    }
    cin >> m;
    vecRight.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> vecRight[i].x >> vecRight[i].y;
    }
    cin >> q;
    vecP.resize(q);
    for (int i = 0; i < q; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    int l = 0, r = 0;
    ld ans = 1e18;
    for (int i = 0; i < n; ++i) {
        while (r + 1 < m && vecRight[r + 1].y < vecLeft[i].y) {
            r++;
        }
        ans = min(ans, segment(vecRight[r], vecRight[r + 1]).its(vecLeft[i].y) - vecLeft[i].x);
    }
    for (int i = 0; i < m; ++i) {
        while (l + 1 < n && vecLeft[l + 1].y < vecRight[i].y) {
            l++;
        }
        ans = min(ans, vecRight[i].x - segment(vecLeft[l], vecLeft[l + 1]).its(vecRight[i].y));
    }
    l = r = 0;
    for (int i = 0; i < q; ++i) {
        if (vecLeft[0].y > vecP[i].y) {
            continue;
        }
        if (vecLeft[n - 1].y < vecP[i].y) {
            break;
        }
        while (l + 1 < n && vecLeft[l + 1].y < vecP[i].y) {
            l++;
        }
        while (r + 1 < m && vecRight[r + 1].y < vecP[i].y) {
            r++;
        }
        ld xleft = segment(vecLeft[l], vecLeft[l + 1]).its(vecP[i].y);
        ld xright = segment(vecRight[r], vecRight[r + 1]).its(vecP[i].y);
        ld maxx = 0;
        vector <int> vecX;
        int ii = i;
        while (vecP[ii].y == vecP[i].y) {
            vecX.push_back(vecP[ii].x);
            ii++;
        }
        i = ii - 1;
        sort(vecX.begin(), vecX.end());
        int st =  - 1, en = - 1;
        for (int j = 0; j < vecX.size(); ++j) {
            if (leq(xleft, vecX[j]) && leq(vecX[j], xright)) {
                maxx = max(maxx, vecX[j] - xleft);
                st = j;
                break;
            }
        }
        for (int j = vecX.size() - 1; j >= 0; --j) {
            if (leq(xleft, vecX[j]) && leq(vecX[j], xright)) {
                maxx = max(maxx, xright - vecX[j]);
                en = j;
                break;
            }
        }
        if (st < en) {
            for (int j = st; j + 1 <= en; ++j) {
                maxx = max(maxx, (ld)vecX[j + 1] - (ld)vecX[j]);
            }
        }
        if (maxx) {
            ans = min(ans, maxx);
        }
    }
    cout << fixed << setprecision(10) << ans;
}

int main() {
    Task();
    Solve();
}
