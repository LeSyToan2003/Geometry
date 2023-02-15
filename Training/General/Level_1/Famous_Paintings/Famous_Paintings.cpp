#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y;

    point() {}
    point(int a, int b) { x = a, y = b; }

    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - (*this))); }
};

int n, cnt = 0;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    for (int i = 0; i < n - 3; ++i) {
        for (int j = i + 1; j < n - 2; ++j) {
            for (int k = j + 1; k < n - 1; ++k) {
                for (int l = k + 1; l < n; ++l) {
                    if (p[i].ccw(p[j], p[k]) && p[i].ccw(p[k], p[l]) && p[j].ccw(p[k], p[l]) && p[i].ccw(p[j], p[l])) {
                        cnt++;
                    }
                }
            }
        }
    }

    cout << cnt;
}

int main() {
    Task();
    Solve();
}
