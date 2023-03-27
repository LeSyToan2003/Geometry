#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int root = 1e6;

int sign(ll a) {
    return a == 0 ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x;
    int y;
    int x1;
    int y1;
    int x2;
    int y2;
    int index;
    bool query;

    point() {}
    point(int a, int b) {
        x = a, y = b;
    }

    bool operator == (point p) {
        return x == p.x && y == p.y;
    }

    bool operator < (point p) {
        return x != p.x ? x < p.x : y < p.y;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }
};

struct line {
    point M;
    point N;
    int index;

    line() {}
    line(point pa, point pb) {
        M = pa, N = pb;
    }

    ld its(ld x) {
        return ((ld)x * (N.y - M.y) + (ld)M.y * N.x - (ld)M.x * N.y) / ((ld)N.x - (ld)M.x);
    }
};

int n;
int m;
int q;
ld x;
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
    ld a = la.its(x);
    ld b = lb.its(x);
    if (a != b) {
        return a < b;
    }
    if (la.index < q || lb.index < q) {
        return false;
    }
    return la.M.ccw(lb.M, lb.N) < 0;
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
            int pre = (j - 1 + m) % m;
            int nxt = (j + 1) % m;
            pts[j].x1 = pts[pre].x;
            pts[j].y1 = pts[pre].y;
            pts[j].x2 = pts[nxt].x;
            pts[j].y2 = pts[nxt].y;
            pts[j].index = i + q;
            pts[j].query = false;
            p.push_back(pts[j]);
        }
    }
    for (int i = 0; i < q; ++i) {
        point pt;
        cin >> pt.x >> pt.y;
        pt.index = i;
        pt.query = true;
        p.push_back(pt);
    }
    sort(p.begin(), p.end());

    parent.resize(n + q);
    for (int i = 0; i < n + q; ++i) {
        parent[i] = root;
    }
    set <line> st;
    for (int i = 0; i < p.size(); ++i) {
        x = p[i].x;
        if (parent[p[i].index] == root) {
            int j = p[i].index;
            line l = line(p[i], point(p[i].x + 1, p[i].y));
            l.index = p[i].index;
            int previous = st.size();
            st.insert(l);
            auto it = st.find(l);
            if (st.size() == previous) {
                parent[j] = parent[(*it).index];
            }
            else {
                it++;
                if (it == st.end()) {
                    parent[j] = j - q;
                }
                else {
                    if (p[i].ccw((*it).M, (*it).N) < 0) {
                        parent[j] = (*it).index - q;
                    }
                    else {
                        parent[j] = parent[(*it).index];
                    }
                }
                st.erase(l);
            }
        }
        if (!p[i].query) {
            point pa = point(p[i].x1, p[i].y1);
            point pb = point(p[i].x2, p[i].y2);
            if (pa.x < p[i].x) {
                line l = line(pa, p[i]);
                st.erase(l);
            }
            if (pb.x < p[i].x) {
                line l = line(p[i], pb);
                st.erase(l);
            }
            if (pa.x > p[i].x) {
                line l = line(pa, p[i]);
                l.index = p[i].index;
                st.insert(l);
            }
            if (pb.x > p[i].x) {
                line l = line(p[i], pb);
                l.index = p[i].index;
                st.insert(l);
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
