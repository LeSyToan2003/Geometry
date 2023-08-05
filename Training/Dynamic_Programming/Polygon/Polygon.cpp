#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    ll area(point pa, point pb) {
        return abs((pa - *this).cross(pb - *this));
    }
};

int n, k;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool Check(ll minn) {
    vector <vector <pair <int, ll>>> vecDP(n + 1, vector <pair <int, ll>> (n + 1, {0, 0}));
    for (int len = 3; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            for (int k = i + 1; k < j; ++k) {
                int cnt = vecDP[i][k].first + vecDP[k][j].first;
                ll area = vecDP[i][k].second + vecDP[k][j].second + vecP[k].area(vecP[i], vecP[j]);
                if (area >= minn) {
                    vecDP[i][j] = max(vecDP[i][j], {cnt + 1, 0});
                } else {
                    vecDP[i][j] = max(vecDP[i][j], {cnt, area});
                }
            }
        }
    }
    return vecDP[1][n].first >= k + 1;
}

void Solve() {
    cin >> n >> k;
    vecP.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    ll l = 1, r = 1e18;
    while (l < r) {
        ll m = (l + r) / 2;
        if (l == m) {
            m++;
        }
        if (Check(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l;
}

int main() {
    Task();
    Solve();
}
