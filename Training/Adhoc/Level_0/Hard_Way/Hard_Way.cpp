#include <bits/stdc++.h>

using namespace std;

struct point {
    int x, y;
};

int T, len;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> T;
    vecP.resize(3);
    while (T--) {
        len = 0;
        for (int i = 0; i < 3; ++i) {
            cin >> vecP[i].x >> vecP[i].y;
        }
        for (int i = 0; i < 3; ++i) {
            int ii = (i + 1) % 3, iii = (i + 2) % 3;
            if (vecP[i].y == vecP[ii].y && vecP[i].y > vecP[iii].y) {
                len += abs(vecP[i].x - vecP[ii].x);
            }

        }
        cout << len << "\n";
    }
}

int main() {
    Task();
    Solve();
}

