#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int MINX = - 1e9 - 9;
const int MAXX = 1e9 + 9;
const int MAXN = 6e5 + 9;
const int MAXD = 1e9 + 9;
const int root = 6e5 + 9;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, x1, y1, x2, y2, index;

    point() {}
    point(int a, int b) { x = a, y = b; }

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

    ld its(int x) { return ((ld)x * (N.y - M.y) + (ld)M.y * N.x - (ld)M.x * N.y) / ((ld)N.x - (ld)M.x); }
};

int n, m, x, diameter, Michael, Lincoln, maxd;
vector <int> parent, dist;
vector <point> p;
vector <vector <int>> adjacent;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (line la, line lb) {
    ld a = la.its(x), b = lb.its(x);
    return a != b ? a < b : la.M.ccw(lb.M, lb.N) < 0;
}

void DFS(int u, int d, int v) {
    if (d > diameter) {
        diameter = d;
        Michael = u;
    }
    for (auto i : adjacent[u]) {
        if (i != v) {
            DFS(i, d + 1, u);
        }
    }
}

void BFS(int u) {
    dist.resize(MAXN);
    for (int i = 0; i < MAXN; ++i) { dist[i] = MAXD; }
    queue <int> Q;
    dist[u] = 0;
    Q.push(u);
    while (Q.size()) {
        int v = Q.front();
        Q.pop();
        for (auto i : adjacent[v]) {
            if (dist[i] > dist[v] + 1) {
                dist[i] = dist[v] + 1;
                Q.push(i);
            }
        }
    }
}

void Find_Diameter() {
    diameter = Michael = 0;
    DFS(root, 0, - 1);
    Lincoln = Michael;
    DFS(Lincoln, 0, - 1);
    maxd = diameter;
    BFS(root);
    maxd += max(dist[Michael], dist[Lincoln]);
}

void Solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> m;
        vector <point> pts(m);
        for (int j = 0; j < m; ++j) {
            cin >> pts[j].x >> pts[j].y;
        }
        reverse(pts.begin(), pts.end());
        for (int j = 0; j < m; ++j) {
            p.push_back(pts[j]);
            p.back().index = i;
            int pre = (j - 1 + m) % m, nxt = (j + 1) % m;
            p.back().x1 = pts[pre].x, p.back().y1 = pts[pre].y, p.back().x2 = pts[nxt].x, p.back().y2 = pts[nxt].y;
        }
    }

    sort(p.begin(), p.end());
    set <line> Tree;

    parent.resize(n);
    for (int i = 0; i < n; ++i) {
        parent[i] = - 1;
    }

    for (int i = 0; i < p.size(); ++i) {
        x = p[i].x;
        int node = p[i].index;
        if (parent[node] == - 1) {
            line l = line(point(MINX, p[i].y), point(MAXX, p[i].y));
            Tree.insert(l);
            auto it = Tree.find(l);
            it++;
            if (it == Tree.end()) {
                parent[node] = root;
            }
            else {
                point pa = (*it).M, pb = (*it).N;
                if (p[i].ccw(pa, pb) < 0) {
                    parent[node] = (*it).index;
                }
                else {
                    parent[node] = parent[(*it).index];
                }
            }
            Tree.erase(l);
        }
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

    adjacent.resize(MAXN);
    for (int i = 0; i < n; ++i) {
        adjacent[i].push_back(parent[i]);
        adjacent[parent[i]].push_back(i);
    }

    Find_Diameter();

    cout << maxd;
}

int main() {
    Task();
    Solve();
}
