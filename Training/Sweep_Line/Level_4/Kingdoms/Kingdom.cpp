#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef double db;

const int MINX = - 1e9;
const int MAXX = 1e9;
const int root = 1e6;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, x1, y1, x2, y2, index;
    bool query;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator == (point p) { return x == p.x && y == p.y; }
    bool operator < (point p) { return x != p.x ? x < p.x : y < p.y; }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    ll operator * (point p) { return (ll)x * p.x + (ll)y * p.y; }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }

    bool on(point pa, point pb) { return ccw(pa, pb) ? false : (pa - *this) * (pb - *this) <= 0; }
};

struct line {
    point M, N;
    int index;

    line() {}
    line(point pa, point pb) { M = pa, N = pb; }

    db its(int x) {
        db a = ((db)N.y - (db)M.y) / ((db)N.x - (db)M.x), b = (db)M.y - a * (db)M.x;
        return a * (db)x + b;
    }
};

int n, m, q, x;
vector <int> parent;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (line la, line lb) {
    if (lb.M.x == MINX) {
        point pa = la.M, pb = la.N;
        if (la.M.x != MINX && point(x, lb.M.y).on(pa, pb)) { return false; }
        if (pb < pa) { swap(pa, pb); }
        return point(x, lb.M.y).ccw(pa, pb) > 0;
    }
    if (la.M.x == MINX) {
        point pa = lb.M, pb = lb.N;
        if (lb.M.x != MINX && point(x, la.M.y).on(pa, pb)) { return true; }
        if (pb < pa) { swap(pa, pb); }
        return point(x, la.M.y).ccw(pa, pb) < 0;
    }
    if (la.M == lb.N) { return la.N.y < lb.M.y; }
    if (la.N == lb.M) { return la.M.y < lb.N.y; }
    return la.its(x) < lb.its(x);
}

void Solve() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> m;
        vector <point> pts(m);
        for (int j = 0; j < m; ++j) {
            cin >> pts[j].x >> pts[j].y;
        }
        for (int j = 0; j < m; ++j) {
            p.push_back(pts[j]);
            int pre = (j - 1 + m) % m, nxt = (j + 1) % m;
            p.back().query = false;
            p.back().index = i + q;
            p.back().x1 = pts[pre].x, p.back().y1 = pts[pre].y, p.back().x2 = pts[nxt].x, p.back().y2 = pts[nxt].y;
        }
    }
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        p.push_back(point(x, y));
        p.back().query = true;
        p.back().index = i;
    }

    sort(p.begin(), p.end());
    tree <line, null_type, less<line>, rb_tree_tag, tree_order_statistics_node_update> Tree;

    parent.resize(n + q);
    for (int i = 0; i < n + q; ++i) {
        parent[i] = root;
    }

    for (int i = 0; i < p.size(); ++i) {
        x = p[i].x;
        if (parent[p[i].index] == root) {
            int node = p[i].index;
            line l = line(point(MINX, p[i].y), point(MAXX, p[i].y));
            Tree.insert(l);
            auto it = Tree.find(l);
            it++;
            if (it == Tree.end()) {
                parent[node] = node - q;
            }
            else {
                point pa = (*it).M, pb = (*it).N;
                if (p[i].ccw(pa, pb) < 0) {
                    parent[node] = (*it).index - q;
                }
                else {
                    parent[node] = parent[(*it).index];
                }
            }
            Tree.erase(l);
        }
        if (!p[i].query) {
            point pa = point(p[i].x1, p[i].y1), pb = point(p[i].x2, p[i].y2);
            if (pa.x < p[i].x) {
                line l = line(pa, p[i]);
                Tree.erase(l);
            }
            if (pb.x < p[i].x) {
                line l = line(p[i], pb);
                Tree.erase(l);
            }
            if (pa.x > p[i].x) {
                line l = line(pa, p[i]);
                l.index = p[i].index;
                Tree.insert(l);
            }
            if (pb.x > p[i].x) {
                line l = line(p[i], pb);
                l.index = p[i].index;
                Tree.insert(l);
            }
        }
    }
    if (p.back().query) {
        parent[p.back().index] = parent[p[p.size() - 2].index];
    }

    for (int i = 0; i < q; ++i) {
        cout << parent[i] + 1 << "\n";
    }
}

int main() {
    Task();
    Solve();
}
