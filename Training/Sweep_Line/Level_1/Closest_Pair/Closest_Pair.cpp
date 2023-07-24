#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1e9;

struct point {
    int x, y, index;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll norm2() {
        return (ll)x * x + (ll)y * y;
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

bool operator < (point pa, point pb) {
    return pa.y != pb.y ? pa.y < pb.y : pa.index < pb.index;
}

bool cmp(point pa, point pb) {
    return pa.x != pb.x ? pa.x < pb.x : pa.y < pb.y;
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
        vecP[i].index = i;
    }
    sort(vecP.begin(), vecP.end(), cmp);
    set <point> setP;
    ll ans = 1e18;
    pair <int, int> pos;
    for (int i = 0; i < n; ++i) {
        int d = ceil(sqrt(ans));
        point p = point(- INF, vecP[i].y - d);
        p.index = vecP[i].index;
        while (true) {
            auto it = setP.upper_bound(p);
            if (it == setP.end() || (*it).y > vecP[i].y + d) break;
            p = *it;
            if (p.x < vecP[i].x - d) {
                setP.erase(p);
                continue;
            }
            ll d1 = (vecP[i] - p).norm2();
            if (d1 < ans) {
                ans = d1;
                pos = {p.index, vecP[i].index};
            }
        }
        setP.insert(vecP[i]);
    }
    if (pos.first > pos.second) {
        swap(pos.first, pos.second);
    }
    cout << pos.first << " " << pos.second << "\n";
    cout << fixed << setprecision(6) << sqrt(ans);
}

int main() {
    Task();
    Solve();
}
