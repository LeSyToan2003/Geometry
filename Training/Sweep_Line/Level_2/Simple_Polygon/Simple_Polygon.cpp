// https://codeforces.com/gym/100486/submit

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, index;
    bool getin;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator == (point p) { return x == p.x && y == p.y; }
    bool operator < (point p) {
        if (x != p.x) { return x < p.x; }
        if (getin != p.getin) { return getin == true; }
        return y < p.y;
    }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    ll operator * (point p) { return (ll)x * p.x + (ll)y * p.y; }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }

    bool on(point pa, point pb) { return ccw(pa, pb) != 0 ? false : (pa - *this) * (pb - *this) < 0; }
};

struct line {
    point M, N;
    int index;

    line() {}
    line(point a, point b, int c) { M = a, N = b, index = c; }

    bool its(line l) {
        if (M.on(l.M, l.N) || N.on(l.M, l.N) || (l.N.on(M, N) || l.M.on(M, N))) { return true; }
        return M.ccw(l.M, l.N) * N.ccw(l.M, l.N) < 0 && l.M.ccw(M, N) * l.N.ccw(M, N) < 0;
    }
};

bool operator < (line la, line lb) {
    int mina = min(la.M.y, la.N.y), minb = min(lb.M.y, lb.N.y);
    if (mina != minb) { return mina < minb; }
    return la.index < lb.index;
}

int n;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    while (cin >> n && n != 0) {
        p.clear();
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }

        map <pair <int, int>, int> mp;
        for (int i = 0; i < n; ++i) {
            mp[{p[i].x, p[i].y}]++;
        }
        bool chk = true;
        for (auto i : mp) {
            if (i.second > 1) {
                chk = false;
                break;
            }
        }
        if (!chk) {
            cout << "NO\n";
            continue;
        }

        vector <line> l(n);
        for (int i = 0; i < n; ++i) {
            int nxt = (i + 1) % n;
            point pa = p[i], pb = p[nxt];
            if (pb.x < pa.x || (pb.x == pa.x && pb.y < pa.y)) {
                swap(pa, pb);
            }
            pa.index = i, pb.index = i;
            l[i] = line(pa, pb, i);
        }
        vector <point> points;
        for (int i = 0; i < n; ++i) {
            points.push_back(l[i].M);
            points.back().getin = true;
            points.push_back(l[i].N);
            points.back().getin = false;
        }
        sort(points.begin(), points.end());

        tree <line, null_type, less<line>, rb_tree_tag, tree_order_statistics_node_update> Tree;
        for (int i = 0; i < points.size(); ++i) {
            line curr = l[points[i].index];
            if (points[i].getin) {
                Tree.insert(curr);
                auto it = Tree.find(curr);
                auto upp = it;
                upp++;
                if (upp != Tree.end()) {
                    if (curr.its(*upp)) {
                        chk = false;
                        break;
                    }
                    upp++;
                    if (upp != Tree.end()) {
                        if (curr.its(*upp)) {
                            chk = false;
                            break;
                        }
                    }
                }
                auto dow = it;
                if (dow != Tree.begin()) {
                    dow--;
                    if (curr.its(*dow)) {
                        chk = false;
                        break;
                    }
                    if (dow != Tree.begin()) {
                        dow--;
                        if (curr.its(*dow)) {
                            chk = false;
                            break;
                        }
                    }
                }
            }
            else {
                auto it = Tree.find(curr);
                auto upp = it;
                upp++;
                auto dow = it;
                if (dow != Tree.begin() && upp != Tree.end()) {
                    dow--;
                    line li = *dow;
                    if (li.its(*upp)) {
                        chk = false;
                        break;
                    }
                }
                Tree.erase(curr);
            }
        }

        cout << chk ? "YES\n" : "NO\n";
    }
}

int main() {
    Task();
    Solve();
}
