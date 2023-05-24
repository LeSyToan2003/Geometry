#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

struct point {
    ld x, y;

    point() {}
    point(ld _x, ld _y) {
        x = _x, y = _y;
    }

    bool operator != (point p) {
        return x != p.x || y != p.y;
    }

    point operator + (point p) {
        return point(x + p.x, y + p.y);
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    point operator / (ld k) {
        return point(x / k, y / k);
    }

    ld norm() {
        return hypot(x, y);
    }
};

vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("geometry.in", "r", stdin);
    freopen("geometry.out", "w", stdout);
}

void Solve() {
    vecP.resize(4);
    while (cin >> vecP[0].x >> vecP[0].y >> vecP[1].x >> vecP[1].y) {
        cin >> vecP[2].x >> vecP[2].y >> vecP[3].x >> vecP[3].y;
        bool chk = false;
        for (auto p : vecP) {
            if (p != point(0, 0)) {
                chk = true;
                break;
            }
        }
        if (!chk) {
            return;
        }
        ld minn = 1e9;
        point pa, pb;
        for (int i = 0; i < 2; ++i) {
            for (int j = 2; j < 4; ++j) {
                ld d = (vecP[i] - vecP[j]).norm();
                if (d < minn) {
                    minn = d;
                    pa = vecP[i];
                    pb = vecP[j];
                }
            }
        }
        point center = (pa + pb) / 2;
        ld radius = minn / 2 + 0.005;
        cout << fixed << setprecision(10) << center.x << " " << center.y << " " << radius << "\n";
    }
}

int main() {
    Task();
    Solve();
}

