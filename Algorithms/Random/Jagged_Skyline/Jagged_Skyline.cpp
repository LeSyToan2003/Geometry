#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int w;
ll h;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool Query(int x, ll y) {
    cout << "? " << x << " " << y << endl;
    string s;
    cin >> s;
    return s == "building";
}

void Answer(int x, ll y) {
    cout << "! " << x << " " << y << endl;
}

void Solve() {
    cin >> w >> h;
    vector <int> vecA(w + 1);
    for (int i = 1; i <= w; ++i) {
        vecA[i] = i;
    }
    random_shuffle(vecA.begin() + 1, vecA.end());
    int x = vecA[1];
    ll maxx = 0;
    for (int i = 1; i <= w; ++i) {
        if (!Query(vecA[i], maxx + 1)) continue;
        ll l = maxx + 1, r = h;
        while (l < r) {
            ll m = (l + r) / 2;
            if (l == m) {
                m++;
            }
            if (Query(vecA[i], m)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        x = vecA[i];
        maxx = l;
        if (maxx == h) break;
    }
    Answer(x, maxx);
}

int main() {
    Task();
    Solve();
}
