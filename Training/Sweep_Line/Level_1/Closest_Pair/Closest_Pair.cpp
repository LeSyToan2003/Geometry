#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

const int MIND = - 1e6 - 9;

struct point {
    int x, y, index;

    point() {}
    point(int a, int b, int c) { x = a; y = b; index = c; }

    point operator - (point p) { return point(x - p.x, y - p.y, 0); }

    ll norm2() { return (ll)x * x + (ll)y * y; }
};

int n;
ll mind = 1e18;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (point pa, point pb) {
    return pa.y != pb.y ? pa.y < pb.y : pa.x < pb.x;
}

bool cmp(point pa, point pb) {
    return pa.x != pb.x ? pa.x < pb.x : pa.y < pb.y;
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    for (int i = 0; i < n; ++i) {
        p[i].index = i;
    }
    sort(p.begin(), p.end(), cmp);

    tree <point, null_type, less<point>, rb_tree_tag, tree_order_statistics_node_update> Tree;
    pair <int, int> pos;
    for (int i = 0; i < n; ++i) {
        int d = (int)ceil(sqrt(mind));
        point pi = point(MIND, p[i].y - d, p[i].index);
        while (true) {
            auto it = Tree.upper_bound(pi);
            pi = *it;
            if (it == Tree.end()) {
                break;
            }
            if (pi.y > p[i].y + d) {
                break;
            }
            if (pi.x < p[i].x - d) {
                Tree.erase(it);
                continue;
            }
            ll dist = (pi - p[i]).norm2();
            if (dist < mind) {
                mind = dist;
                pos = {pi.index, p[i].index};
            }
        }
        Tree.insert(p[i]);
    }

    if (pos.first > pos.second) {
        swap(pos.first, pos.second);
    }

    cout << pos.first << " " << pos.second << " ";
    cout << fixed << setprecision(6) << sqrt(mind);
}

int main() {
    Task();
    Solve();
}
