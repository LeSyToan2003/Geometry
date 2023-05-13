#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T;
ll a, b, c;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        cout << a + b + c - 1 << "\n";
    }
}

int main() {
    Task();
    Solve();
}
