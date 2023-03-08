#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1e9;

int sign(ll a) {
    return a == 0 ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y;

    point() {}
    point(int x, int y) {
        (*this).x = x;
        (*this).y = y;
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

int n, cnt, ind;
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

    int minc = INF;
    for (int i = 0; i < n; ++i) {
        int c = 0;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (p[i].ccw(p[j], p[k])) {
                    c++;
                }
            }
        }
        c /= 2;
        if (c < minc) {
            minc = c;
            ind = i + 1;
        }
        cnt += c;
    }
    cnt /= 3;

    cout << cnt << " " << ind;
}

int main() {
    Task();
    Solve();
}
