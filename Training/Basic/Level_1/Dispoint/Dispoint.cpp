#include <bits/stdc++.h>

using namespace std;

const int MINC = - 1e9;
const int MAXC = 1e9;

int n;
vector <int> x, y;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    x.resize(n), y.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> y[i];
    }

    int minx, maxx, miny, maxy;
    minx = miny = MAXC;
    maxx = maxy = MINC;
    vector <int> xx = x, yy = y;
    for (int i = 0; i < n; ++i) {
        x[i] = xx[i] + yy[i];
        minx = min(minx, x[i]);
        maxx = max(maxx, x[i]);
    }
    for (int i = 0; i < n; ++i) {
        y[i] = yy[i] - xx[i];
        miny = min(miny, y[i]);
        maxy = max(maxy, y[i]);
    }


    for (int i = 0; i < n; ++i) {
        int ans = max(max(x[i] - minx, maxx - x[i]), max(y[i] - miny, maxy - y[i]));
        cout << ans << " ";
    }
}

int main() {
    Task();
    Solve();
}
