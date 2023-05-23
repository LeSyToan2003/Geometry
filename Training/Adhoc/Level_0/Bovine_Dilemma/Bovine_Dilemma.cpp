#include <bits/stdc++.h>

using namespace std;

int T, n;
vector <int> vecX;

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
        cin >> n;
        vecX.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> vecX[i];
        }
        set <int> setX;
        for (int i = 0; i + 1 < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                setX.insert(vecX[j] - vecX[i]);
            }
        }
        cout << setX.size() << "\n";
    }
}

int main() {
    Task();
    Solve();
}

