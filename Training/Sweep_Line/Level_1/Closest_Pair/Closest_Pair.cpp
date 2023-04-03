#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int INF = 1e9;

struct point {
    int x, y, id;

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
ll mind;
pair <int, int> id;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (point a, point b) {
    return a.y != b.y ? a.y < b.y : a.id < b.id;
}

bool cmp(point a, point b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

void Solve() {
    mind = (ll)INF * INF;
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
        vecP[i].id = i;
    }
    sort(vecP.begin(), vecP.end(), cmp);
    set <point> setP;
    for (int i = 0; i < n; ++i) {
        int d = (int)ceil(sqrt(mind));
        point p = point( - INF, vecP[i].y - d);
        p.id = vecP[i].id;
        while (true) {
            auto it = setP.upper_bound(p);
            if (it == setP.end() || (*it).y > vecP[i].y + d) break;
            p = *it;
            if (p.x < vecP[i].x - d) {
                setP.erase(p);
                continue;
            }
            ll currd = (p - vecP[i]).norm2();
            if (currd < mind) {
                mind = currd;
                id = {p.id, vecP[i].id};
            }
        }
        setP.insert(vecP[i]);
    }
    if (id.first > id.second) swap(id.first, id.second);
    cout << id.first << " " << id.second << " ";
    cout << fixed << setprecision(6) << sqrt(mind);
}

int main() {
    Task();
    Solve();
}
