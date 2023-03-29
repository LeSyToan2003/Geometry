#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld INF = 1e9 + 9;

struct triangle {
    int x, y, m;

    bool operator < (triangle tri) {
        return y < tri.y;
    }
};

int n;
ld area;
vector <triangle> vecTri;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

ld Area(int xl, int xr, int x) {
    return 1.0 * (x - xl) * (x - xl) / 2 - (x > xr) * 1.0 * (x - xr) * (x - xr) / 2;
}

void Solve() {
    cin >> n;
    vecTri.resize(n);
    vector <int> vecX;
    for (int i = 0; i < n; ++i) {
        cin >> vecTri[i].x >> vecTri[i].y >> vecTri[i].m;
        vecX.push_back(vecTri[i].x);
    }
    vecX.push_back(INF);
    sort(vecTri.begin(), vecTri.end());
    sort(vecX.begin(), vecX.end());
    vecX.erase(unique(vecX.begin(), vecX.end()), vecX.end());
    for (int i = 0; i + 1 < vecX.size(); ++i) {
        int preX = vecX[i], preY;
        for (auto tri : vecTri) {
            if (tri.x <= vecX[i] && tri.x + tri.m > vecX[i]) {
                if (preX > vecX[i]) {
                    preX -= tri.y - preY;
                    preY = tri.y;
                }
                if (tri.x + tri.m > preX) {
                    area += Area(vecX[i], vecX[i + 1], tri.x + tri.m);
                    if (preX > vecX[i]) {
                        area -= Area(vecX[i], vecX[i + 1], preX);
                    }
                    preX = tri.x + tri.m;
                    preY = tri.y;
                }
            }
        }
    }
    cout << fixed << setprecision(1) << area;
}

int main() {
    Task();
    Solve();
}
