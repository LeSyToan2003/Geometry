#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int MINX = - 1e9 - 9;
const int MAXX = 1e9 + 9;
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

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

struct line {
    point M, N;
    int index;

    line() {}
    line(point pa, point pb) { M = pa, N = pb; }

    ld its(int x) { return ((ld)x * (N.y - M.y) + (ld)M.y * N.x - (ld)M.x * N.y) / ((ld)N.x - (ld)M.x) ; }
};

int w, h, n, m, q, x;
vector <int> parent;
vector <ll> a, area;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (line la, line lb) {
    ld a = la.its(x), b = lb.its(x);
    return (a != b) ? a < b : la.M.ccw(lb.M, lb.N) < 0;
}

ll Area(vector <point> &p) {
    ll area = 0;
    for (int i = 0; i < p.size(); ++i) {
        int ii = (i + 1) % p.size();
        area += p[i].det(p[ii]);
    }
    return abs(area);
}

void Solve() {
    cin >> w >> h >> n >> m >> q;
    a.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        vector <point> pts(m);
        for (int j = 0; j < m; ++j) {
            cin >> pts[j].x >> pts[j].y;
        }
        for (int j = 0; j < m; ++j) {
            p.push_back(pts[j]);
            p.back().query = false;
            p.back().index = i + q;
            int pre = (j - 1 + m) % m, nxt = (j + 1) % m;
            p.back().x1 = pts[pre].x, p.back().y1 = pts[pre].y, p.back().x2 = pts[nxt].x, p.back().y2 = pts[nxt].y;
        }
        a[i] = Area(pts);
    }
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        p.push_back(point(x, y));
        p.back().query = true;
        p.back().index = i;
    }

    vector <point> pts = {{0, 0}, {0, h}, {w, h}, {w, 0}};
    for (int i = 0; i < 4; ++i) {
        p.push_back(pts[i]);
        p.back().query = false;
        p.back().index = n + q;
        int pre = (i - 1 + 4) % 4, nxt = (i + 1) % 4;
        p.back().x1 = pts[pre].x, p.back().y1 = pts[pre].y, p.back().x2 = pts[nxt].x, p.back().y2 = pts[nxt].y;
    }
    a[n] = Area(pts);

    area = a;

    sort(p.begin(), p.end());
    set <line> Tree;

    parent.resize(n + q + 1);
    for (int i = 0; i < n + q; ++i) {
        parent[i] = root;
    }
    parent.back() = n;

    for (int i = 0; i < p.size(); ++i) {
        int node = p[i].index;
        x = p[i].x;
        if (parent[node] == root) {
            line l = line(point(MINX, p[i].y), point(MAXX, p[i].y));
            Tree.insert(l);
            auto it = Tree.find(l);
            it++;
            point pa = (*it).M, pb = (*it).N;
            if (p[i].ccw(pa, pb) < 0) {
                parent[node] = (*it).index - q;
            }
            else {
                parent[node] = parent[(*it).index];
            }
            if (node >= q) {
                area[parent[node]] -= a[node - q];
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
            if (p[i].x < pa.x) {
                line l = line(pa, p[i]);
                l.index = p[i].index;
                Tree.insert(l);
            }
            if (p[i].x < pb.x) {
                line l = line(p[i], pb);
                l.index = p[i].index;
                Tree.insert(l);
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << fixed << setprecision(1) << area[parent[i]] / 2.0 << "\n";
    }
}

int main() {
    Task();
    Solve();
}
