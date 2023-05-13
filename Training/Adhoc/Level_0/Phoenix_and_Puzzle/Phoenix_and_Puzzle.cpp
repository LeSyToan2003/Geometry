#include <bits/stdc++.h>

using namespace std;

int T, n;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool isSquare(int n) {
    int a = sqrt(n);
    return a * a == n;
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        if (!(n % 2) && isSquare(n / 2)) {
            cout << "YES\n";
        } else if (!(n % 4) && isSquare(n / 4)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    Task();
    Solve();
}
