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

    ll norm2() {
        return (ll)x * x + (ll)y * y;
    }

    point rotating(point p) {
        return point(- y + p.x + p.y, x - p.x + p.y);
    }
};

int n, minn;
vector <point> vecMole, vecHome;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool isSquare(vector <point> &vecP) {
    vector <ll> a;
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            a.push_back((vecP[i] - vecP[j]).norm2());
        }
    }
    sort(a.begin(), a.end());
    return a[0] && a[0] == a[3] && a[4] == a[5] && a[0] * 2 == a[4];
}

void Solve() {
    cin >> n;
    while (n--) {
        vecMole.resize(4), vecHome.resize(4);
        minn = 13;
        for (int i = 0; i < 4; ++i) {
            cin >> vecMole[i].x >> vecMole[i].y >> vecHome[i].x >> vecHome[i].y;
        }
        vector <vector <point>> vecP(4);
        for (int i = 0; i < 4; ++i) {
            vecP[i].push_back(vecMole[i]);
            for (int j = 1; j < 4; ++j) {
                vecP[i].push_back(vecP[i][j - 1].rotating(vecHome[i]));
            }
        }
        for (int i0 = 0; i0 < 4; ++i0) {
            for (int i1 = 0; i1 < 4; ++i1) {
                for (int i2 = 0; i2 < 4; ++i2) {
                    for (int i3 = 0; i3 < 4; ++i3) {
                        vector <point> vecPts = {vecP[0][i0], vecP[1][i1], vecP[2][i2], vecP[3][i3]};
                        if (isSquare(vecPts)) {
                            minn = min(minn, i0 + i1 + i2 + i3);
                        }
                    }
                }
            }
        }
        cout << (minn == 13 ? - 1 : minn) << "\n";
    }
}
int main() {
    Task();
    Solve();
}
