#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;

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

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }
};

int n;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

ll Area(vector <point> &vecP) {
    ll ans = 0;
    int n = vecP.size();
    for (int i = 0; i <= n - 1; ++i) {
        int iNext = (i + 1) % n;
        ans += vecP[i].cross(vecP[iNext]);
    }
    return ans;
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i <= n - 1; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    if (Area(vecP) < 0) {
        reverse(vecP.begin(), vecP.end());
    }
    vector <vector <ll>> vecDP(n, vector <ll> (n, 0));
    for (int i = 0; i + 1 <= n - 1; ++i) {
        vecDP[i][i + 1] = 1;
    }
    for (int l = 3; l <= n; ++l) {
        for (int i = 0; i + l - 1 <= n - 1; ++i) {
            int j = i + l - 1;
            for (int k = i + 1; k <= j - 1; ++k) {
                if (vecP[i].ccw(vecP[k], vecP[j]) > 0) {
                    vecDP[i][j] = (vecDP[i][j] + (vecDP[i][k] * vecDP[k][j]) % mod) % mod;
                }
            }
        }
    }
    cout << vecDP[0][n - 1];
}

int main() {
    Task();
    Solve();
}
