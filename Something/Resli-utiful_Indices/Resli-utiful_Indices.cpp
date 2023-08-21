#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

int T, n, k;
vector <ll> vecFactorial;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

ll Pow(ll a, ll b) {
    if (!b) {
        return 1;
    }
    ll c = Pow(a, b / 2), ans = (c * c) % MOD;
    if (b % 2) {
        ans = (ans * a) % MOD;
    }
    return ans;
}

ll Combination(int n, int k) {
    return (vecFactorial[n] * Pow((vecFactorial[k] * vecFactorial[n - k]) % MOD, MOD - 2)) % MOD;
}

void Solve() {
    vecFactorial.resize(2e5 + 1);
    vecFactorial[0] = 1;
    for (int i = 1; i <= 2e5; ++i) {
        vecFactorial[i] = (vecFactorial[i - 1] * i) % MOD;
    }
    cin >> T;
    while (T--) {
        cin >> n >> k;
        vector <bool> vecStatus(n + 1, true);
        while (k--) {
            int a;
            cin >> a;
            vecStatus[a] = false;
        }
        int cnt = 0, N = n;
        ll ans = 1;
        for (int i = 1; i <= n; ++i) {
            if (vecStatus[i]) {
                cnt++;
            } else {
                if (cnt) {
                    cnt++;
                    ans = (ans * Combination(N, cnt)) % MOD;
                    N -= cnt;
                }
                cnt = 0;
            }
        }
        if (cnt) {
            ans = (ans * Combination(N, cnt)) % MOD;
        }
        N -= cnt;
        if (N) {
            ans = (ans * vecFactorial[N]) % MOD;
        }
        cout << ans << "\n";
    }
}

int main() {
    Task();
    Solve();
}
