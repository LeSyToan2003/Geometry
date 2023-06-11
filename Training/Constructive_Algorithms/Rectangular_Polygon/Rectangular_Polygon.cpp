#include <bits/stdc++.h>

using namespace std;

int n;
vector <int> vecL;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
}

void Solve() {
    cin >> n;
    vecL.resize(n + 1);
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> vecL[i];
        s += vecL[i];
    }
    vector <vector <int>> dp(n + 1), trace(n + 1);
    for (int i = 0; i <= n; ++i) {
        dp[i].assign(s, - 1);
        trace[i].resize(s);
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= s / 2; ++j) {
            if (dp[i - 1][j] != - 1) {
                if (dp[i][j + vecL[i]] < dp[i - 1][j] + 1) {
                    dp[i][j + vecL[i]] = dp[i - 1][j] + 1;
                    trace[i][j + vecL[i]] = j;
                }
                if (j >= vecL[i] && dp[i][j - vecL[i]] < dp[i - 1][j] + 1) {
                    dp[i][j - vecL[i]] = dp[i - 1][j] + 1;
                    trace[i][j - vecL[i]] = j;
                }
                if (dp[i][j] < dp[i - 1][j]) {
                    dp[i][j] = dp[i - 1][j];
                    trace[i][j]= j;
                }
            }
        }
    }
    if (!dp[n][0]) {
        return void(cout << 0);
    }
    cout << dp[n][0] << "\n";
    vector <int> vecLeft, vecRight;
    int prev = 0, curr;
    for (int i = n; i >= 1; --i) {
        curr = trace[i][prev];
        if (curr > prev) {
            vecLeft.push_back(curr - prev);
        } else if (curr < prev) {
            vecRight.push_back(prev - curr);
        }
        prev = curr;
    }
    int x = 0, y = 0;
    for (auto i : vecLeft) {
        cout << x << " " << y << "\n";
        x += i;
        cout << x << " " << y << "\n";
        y++;
    }
    y = - 1;
    for (auto i : vecRight) {
        cout << x << " " << y << "\n";
        x -= i;
        cout << x << " " << y << "\n";
        y--;
    }
}

int main() {
    Task();
    Solve();
}
