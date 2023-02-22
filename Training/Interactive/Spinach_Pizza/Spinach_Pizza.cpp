#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXAREA = 1e18;

struct point {
    int x, y, index;

    bool operator != (point p) { return x != p.x || y != p.y; }

    ll area(point pa, point pb) { return abs(((ll)pa.x - x) * (pb.y - y) - ((ll)pa.y - y) * (pb.x - x)); }
};

int n, ind;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Delete(point pa) {
    vector <point> result;
    for (int i = 0; i < p.size(); ++i) {
        if (p[i] != pa) {
            result.push_back(p[i]);
        }
    }
    p = result;
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    for (int i = 0; i < n; ++i) {
        p[i].index = i + 1;
    }
    vector <point> pinit = p;

    if (n % 2) {
        cout << "Beatrice" << endl;
        cin >> ind;
        Delete(pinit[ind - 1]);
    }
    else {
        cout << "Alberto" << endl;
    }

    while (p.size() > 2) {
        ll mina = MAXAREA;
        n = p.size();
        for (int i = 0; i < n; ++i) {
            int pre = (i - 1 + n) % n, nxt = (i + 1) % n;
            ll a = p[i].area(p[pre], p[nxt]);
            if (a < mina) {
                mina = a;
                ind = p[i].index;
            }
        }
        cout << ind << endl;
        Delete(pinit[ind - 1]);
        cin >> ind;
        Delete(pinit[ind - 1]);
    }
}

int main() {
    Task();
    Solve();
}
