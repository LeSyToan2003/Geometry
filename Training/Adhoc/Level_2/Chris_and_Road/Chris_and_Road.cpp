#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct point {
    int x, y;
};

int n, w, v, u;
ld ans;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n >> w >> v >> u;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    bool chk = true;
    for (int i = 0; i < n; ++i) {
        if ((ll)vecP[i].x * u < (ll)vecP[i].y * v) {
            chk = false;
            break;
        }
    }
    ans = (ld)w / u;
    if (!chk) {
        for (int i = 0; i < n; ++i) {
            if ((ll)vecP[i].x * u > (ll)vecP[i].y * v) {
                ans = max(ans, (ld)vecP[i].x / v + (ld)(w - vecP[i].y) / u);
            }
        }
    }
    cout << fixed << setprecision(10) << ans;
}

int main() {
    Task();
    Solve();
}
