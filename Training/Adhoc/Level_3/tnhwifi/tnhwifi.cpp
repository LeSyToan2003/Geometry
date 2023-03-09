#include <bits/stdc++.h>

using namespace std;

int m, n, k, x, y, r, b, maxs, cnt;
vector <vector <int>> speed;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> m >> n >> k;
    m--, n--;
    speed.resize(n + 9);
    for (int i = 0; i < n + 9; ++i) {
        speed[i].resize(m + 9);
    }
    while (k--) {
        cin >> x >> y >> r >> b;
        x--, y--;
        for (int i = max(0, x - r); i <= min(n, x + r); ++i) {
            int left = max(0, y - (int)sqrt(r * r - (x - i) * (x - i)));
            int right = min(m, y + (int)sqrt(r * r - (x - i) * (x - i)));
            speed[i][left] += b;
            speed[i][right + 1] -= b;
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j > 0) {
                speed[i][j] += speed[i][j - 1];
            }
            maxs = max(maxs, speed[i][j]);
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (speed[i][j] == maxs) {
                cnt++;
            }
        }
    }

    cout << maxs << "\n" << cnt;
}

int main() {
    Task();
    Solve();
}
