#include <bits/stdc++.h>

using namespace std;

int n, x, y;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    int cntr = 0, cntl = 0;
    while (n--) {
        cin >> x >> y;
        if (x > 0) {
            cntr++;
        } else {
            cntl++;
        }
    }
    cout << (cntr <= 1 || cntl <= 1 ? "Yes" : "No");
}

int main() {
    Task();
    Solve();
}
