#include <bits/stdc++.h>

using namespace std;

int n;
vector <int> a;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    cout << (a[0] + a[1] > a[n - 1] ? "KHONG" : "CO");
}

int main() {
    Task();
    Solve();
}
