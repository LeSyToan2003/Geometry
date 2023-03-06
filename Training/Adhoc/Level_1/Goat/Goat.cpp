#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld pi = acos(- 1);

int r;
ld covered;
vector <int> a;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    a.resize(3);
    for (int i = 0; i < 3; ++i) {
        cin >> a[i];
    }
    cin >> r;

    ld peri = (a[0] + a[1] + a[2]) / 2.0;
    ld area = sqrt(peri * (peri - a[0]) * (peri - a[1]) * (peri - a[2]));
    covered = area;
    for (int i = 0; i < 3; ++i) {
        int pre = (i - 1 + 3) % 3, nxt = (i + 1) % 3;
        ld angle = acos(((ld)a[pre] * a[pre] + (ld)a[nxt] * a[nxt] - (ld)a[i] * a[i]) / (2 * (ld)a[pre] * a[nxt]));
        ld A = r * r / tan(angle / 2);
        ld B = r * r * (pi - angle) / 2;
        covered -= A - B;
    }
    covered /= area;

    cout << fixed << setprecision(10) << covered;
}

int main() {
    Task();
    Solve();
}
