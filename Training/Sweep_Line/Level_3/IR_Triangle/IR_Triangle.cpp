#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y;

    point() {}
    point(int a, int b) { x = a, y = b; }

    point operator - (point p) { return point(x - p.x, y - p.y); }
    ll operator * (point p) { return (ll)x * p.x + (ll)y * p.y; }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
    bool on(point pa, point pb) { return ccw(pa, pb) != 0 ? false : (pa - *this) * (pb - *this) < 0; }

    int inp(vector <point> &p) {
        int n = p.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int ii = (i + 1) % n;
            if (on(p[i], p[ii]) == 1) { return 2; }
            point u = p[i], v = p[ii];
            if (u.y < v.y) { swap(u, v); }
            if (y <= v.y || y > u.y) { continue; }
            if (u.ccw(*this, v) == 1) { cnt ^= 1; }
        }
        return cnt;
    }
};

struct line {
    point M, N;

    line() {}
    line(point pa, point pb) { M = pa, N = pb; }

    bool its(line l) {
        if (M.on(l.M, l.N) == 1 || N.on(l.M, l.N) == 1 || l.M.on(M, N) == 1 || l.N.on(M, N) == 1) { return true; }
        return M.ccw(l.M, l.N) * N.ccw(l.M, l.N) < 0 && l.M.ccw(M, N) * l.N.ccw(M, N) < 0;
    }
    point pits1(line l) { return point(M.x, l.M.y - (M.x - l.M.x)); }
    point pits2(line l) { return point(l.M.x + (l.M.y - M.y), M.y); }
};

line lc;
bool operator < (line la, line lb) {
    int ya, yb;
    if (la.M.y == la.N.y) { ya = la.M.y; }
    else { ya = lc.pits1(la).y; }
    if (lb.M.y == lb.N.y) { yb = lb.M.y; }
    else { yb = lc.pits1(lb).y; }
    return ya != yb ? ya < yb : la.M.y != la.N.y;
}

int n;
vector <vector <point>> tri;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    tri.resize(n);
    for (int i = 0; i < n; ++i) {
        int x, y, m;
        cin >> x >> y >> m;
        tri[i].resize(3);
        tri[i][0] = point(x, y);
        tri[i][1] = point(x, y + m);
        tri[i][2] = point(x + m, y);
    }

    vector <vector <point>> pts;
    for (int i = 0; i < n; ++i) {
        bool chk = true;
        for (int j = 0; j < n; ++j) {
            if (i != j && tri[i][0].inp(tri[j]) && tri[i][1].inp(tri[j]) && tri[i][2].inp(tri[j])) {
                chk = false;
                break;
            }
        }
        if (chk) {
            pts.push_back(tri[i]);
        }
    }
    tri = pts;
    n = tri.size();

    set <int> st;
    for (auto p : tri) {
        for (auto i : p) {
            st.insert(i.x);
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (line(tri[i][0], tri[i][1]).its(line(tri[j][1], tri[j][2]))) {
                st.insert(line(tri[i][0], tri[i][1]).pits1(line(tri[j][1], tri[j][2])).x);
            }
            if (line(tri[i][2], tri[i][0]).its(line(tri[j][1], tri[j][2]))) {
                st.insert(line(tri[i][2], tri[i][0]).pits2(line(tri[j][1], tri[j][2])).x);
            }
            if (line(tri[j][0], tri[j][1]).its(line(tri[i][1], tri[i][2]))) {
                st.insert(line(tri[j][0], tri[j][1]).pits1(line(tri[i][1], tri[i][2])).x);
            }
            if (line(tri[j][2], tri[j][0]).its(line(tri[i][1], tri[i][2]))) {
                st.insert(line(tri[j][2], tri[j][0]).pits2(line(tri[i][1], tri[i][2])).x);
            }
        }
    }

    vector <int> xx;
    for (auto i : st) {
        xx.push_back(i);
    }
    db area = 0;
    for (int i = 1; i < xx.size(); ++i) {
        int x = xx[i] - xx[i - 1];
        vector <line> l;
        line la = line(point(xx[i - 1], - 2e7), point(xx[i - 1], 2e7));
        line lb = line(point(xx[i], - 2e7), point(xx[i], 2e7));
        for (auto p : tri) {
            if (line(p[1], p[2]).its(la) && line(p[1], p[2]).its(lb)) {
                l.push_back(line(p[1], p[2]));
            }
            if (line(p[2], p[0]).its(la) && line(p[2], p[0]).its(lb)) {
                l.push_back(line(p[2], p[0]));
            }
        }
        lc = la;
        sort(l.begin(), l.end());
        for (int j = l.size() - 1; j >= 0; --j) {
            line upp = l[j];
            int cnt = 0;
            while (true) {
                if (l[j].M.y != l[j].N.y) {
                    cnt++;
                }
                else {
                    cnt--;
                }
                if (cnt == 0) {
                    break;
                }
                j--;
            }
            line dow = l[j];
            point p = la.pits1(upp), q = lb.pits1(upp);
            area += (db)x * (q.y - dow.M.y) + (db)x * (p.y - q.y) / 2;
        }
    }

    cout << fixed << setprecision(1) << area;
}

int main() {
    Task();
    Solve();
}
