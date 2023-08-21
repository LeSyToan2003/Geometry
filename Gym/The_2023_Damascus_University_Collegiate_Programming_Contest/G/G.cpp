#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T, n;
vector <int> vecA, vecSum;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

int Count(int a, int b) {
    return vecSum[a + b] - vecSum[a] - vecSum[b];
}

void Solve() {
    vecSum.resize(2e5 + 1);
    vecSum[0] = 0;
    for (int i = 1; i <= 2e5; ++i) {
        vecSum[i] = vecSum[i - 1] + (int)sqrt(i);
    }
    vector <pair <bool, ll>> vecDP(1e5 + 1, {false, - 1});
    cin >> T;
    while (T--) {
        cin >> n;
        vecA.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> vecA[i];
        }
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            int x = vecA[i];
            ll maxx = 0;
            for (int j = 2; j <= 447; ++j) {
                int k = j * j, y = k - x;
                if (1 <= y && y <= 1e5 && vecDP[y].first) {
                    maxx = max(maxx, vecDP[y].second + (ll)Count(x, y));
                }
            }
            vecDP[x].first = true;
            vecDP[x].second = max(vecDP[x].second, maxx);
            ans = max(ans, maxx);
        }
        cout << ans << "\n";
        for (int i = 1; i <= n; ++i) {
            int x = vecA[i];
            vecDP[x] = {false, - 1};
        }
    }
}

int main() {
    Task();
    Solve();
}
