#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, index;

    point() {}
    point(int a, int b) { x = a, y = b; }

    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

int T, n;
vector <int> ind;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        p.clear();
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }

        for (int i = 0; i < n; ++i) {
            p[i].index = i + 1;
        }
        vector <vector <point>> points(n);
        int sz = 0;
        points[sz].push_back(p.back());
        ind.clear();
        ind.resize(n);
        for (int i = 0; i < n; ++i) {
            ind[i] = - 1;
        }

        for (int i = n - 2; i >= 0; --i) {
            if (p[i].y <= p[i + 1].y) {
                sz++;
            }
            else while (sz > 0 && points[sz].back().y < points[sz - 1].back().y && points[sz - 1].back().y < p[i].y) {
                points[sz].clear();
                sz--;
            }
            while (points[sz].size() > 1 && p[i].ccw(points[sz].back(), points[sz][points[sz].size() - 2]) >= 0) {
                points[sz].pop_back();
            }
            if (points[sz].size()) {
                ind[i] = points[sz].back().index;
            }
            points[sz].push_back(p[i]);
        }

        for (auto i : ind) {
            cout << i << " ";
        }
        cout << "\n";
    }
}

int main() {
    Task();
    Solve();
}
