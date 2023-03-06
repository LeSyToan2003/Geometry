#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;

    ll cnt = 2LL * n * n + 2LL * n + 1;

    cout << cnt;
}

int main() {
    Task();
    Solve();
}
