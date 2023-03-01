#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, a, b, c, f;
vector <int> h;
ll energy, coin;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    h.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    cin >> a >> b >> c >> f;

    int maxh = h[0], posm = 0;
    for (int i = 1; i < n; ++i) {
        if (h[i] > maxh) {
            maxh = h[i];
            posm = i;
        }
    }
    energy = (ll)maxh * a + (ll)n * b + (ll)maxh * c;

    ll cnt = 0;
    maxh = h[n - 1];
    for (int i = n - 2; i > posm; --i) {
        if (h[i] < maxh) {
            cnt += (ll)maxh - (ll)h[i];
        }
        maxh = max(maxh, h[i]);
    }
    maxh = h[0];
    for (int i = 1; i < posm; ++i) {
        if (h[i] < maxh) {
            cnt += (ll)maxh - (ll)h[i];
        }
        maxh = max(maxh, h[i]);
    }
    coin = cnt * f;

    cout << energy << " " << coin;
}

int main() {
    Task();
    Solve();
}
