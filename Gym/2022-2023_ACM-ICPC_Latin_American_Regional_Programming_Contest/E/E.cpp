#include <bits/stdc++.h>

using namespace std;

int n, K, a;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n >> K >> a;
    int b = n - K - a;
    vector <vector <bool>> vecDP(a + 1, vector <bool> (b + 1, false));
    vecDP[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        if (i == K) {
            continue;
        }
        for (int j = a; j >= 0; --j) {
            for (int k = b; k >= 0; --k) {
                if ((j >= i && vecDP[j - i][k]) || (k >= i && vecDP[j][k - i])) {
                    vecDP[j][k] = true;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (vecDP[i][j]) {
                ans = max(ans, i + j + K);
            }
        }
    }
    ans = n - ans;
    cout << ans;
}

int main() {
    Task();
    Solve();
}
