#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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
        return ccw(pa, pb) ? false : (pa - *this).dot(pb - *this) <= 0;
    }

    bool insp(vector <point> &p) {
        int n = p.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (on(p[i], p[ii])) {
                return true;
            }
            point pa = p[i], pb = p[ii];
            if (pb.y < pa.y) {
                swap(pa, pb);
            }
            if (pa.y < y && y <= pb.y && ccw(pa, pb) < 0) {
                cnt ^= 1;
            }
        }
        return cnt;
    }

    bool incp(vector <point> &p) {
        int n = p.size();
        if (on(p[0], p[1]) || on(p[0], p[n - 1])) {
            return false;
        }
        int l = 2, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(p[0], p[m]) <= 0) {
                r = m;
            }
            else {
                l = m + 1;
            }
        }
        if (on(p[r - 1], p[r])) {
            return false;
        }
        vector <point> tri = {p[0], p[r - 1], p[r]};
        return insp(tri);
    }
};

int n, m;
point pa;
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
    cin >> m;

    while (m--) {
        cin >> pa.x >> pa.y;
        if (pa.incp(p)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}

int main() {
    Task();
    Solve();
}
