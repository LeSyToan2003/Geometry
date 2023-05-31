#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct point {
    int x, y, index;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    ll area(point pa, point pb) {
        return abs((pa - *this).cross(pb - *this));
    }
};

int n;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Delete(int index) {
    vector <point> vecPts;
    int n = vecP.size();
    for (int i = 0; i < n; ++i) {
        if (vecP[i].index + 1 != index) {
            vecPts.push_back(vecP[i]);
        }
    }
    vecP = vecPts;
}

int Minimum() {
    ll minarea = 1e18;
    int n = vecP.size(), index;
    for (int i = 0; i < n; ++i) {
        int ii = (i - 1 + n) % n, iii = (i + 1) % n;
        ll a = vecP[i].area(vecP[ii], vecP[iii]);
        if (a < minarea) {
            minarea = a;
            index = vecP[i].index + 1;
        }
    }
    Delete(index);
    return index;
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
        vecP[i].index = i;
    }
    int index;
    if (!(n % 2)) {
        cout << "Alberto" << endl;
    } else {
        cout << "Beatrice" << endl;
        cin >> index;
        Delete(index);
    }
    while (vecP.size() > 2) {
        cout << Minimum() << endl;
        cin >> index;
        Delete(index);
    }
}

int main() {
    Task();
    Solve();
}
