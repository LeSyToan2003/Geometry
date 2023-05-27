#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ld norm() {
        return hypot(x, y);
    }
};

int n;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("bomb.in", "r", stdin);
    freopen("bomb.out", "w", stdout);
}

void Solve() {
    vecP.resize(3);
    for (int i = 0; i < 3; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    ld sum = 0;
    vector <ld> vecA(3);
    for (int i = 0; i < 3; ++i) {
        int ii = (i + 1) % 3, iii = (i + 2) % 3;
        vecA[i] = (vecP[ii] - vecP[iii]).norm();
        sum += vecA[i];
    }
    sum /= 2;
    for (int i = 0; i < 3; ++i) {
        cout << fixed << setprecision(10) << sum - vecA[i] << "\n";
    }
}

int main() {
    Task();
    Solve();
}
