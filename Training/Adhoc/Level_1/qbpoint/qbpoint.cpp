#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct point {
    int x, y;

    point() {}
    point(int x, int y) {
        (*this).x = x;
        (*this).y = y;
    }

    bool operator < (point p) {
        return y != p.y ? y < p.y : x < p.x;
    }
    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    int cross(point p) {
        return x * p.y - y * p.x;
    }
};

int n;
ll cnt;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool cmp(point pa, point pb) {
    return pa.cross(pb) > 0;
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    sort(p.begin(), p.end());

    for (int i = 0; i + 2 < n; ++i) {
        vector <point> pts;
        for (int j = i + 1; j < n; ++j) {
            pts.push_back(p[j] - p[i]);
        }
        sort(pts.begin(), pts.end(), cmp);
        int m = pts.size(), c = 1;
        for (int j = 1; j < m; ++j) {
            if (!pts[j].cross(pts[j - 1])) {
                c++;
            }
            if (j == m - 1 || pts[j].cross(pts[j - 1])) {
                cnt += (ll)c * (c - 1) / 2;
                c = 1;
            }
        }
    }

    cout << cnt;
}

int main() {
    Task();
    Solve();
}
