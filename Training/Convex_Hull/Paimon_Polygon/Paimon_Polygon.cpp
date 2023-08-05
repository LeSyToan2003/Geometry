#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, index;
    bool joined, isfault;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point p) { return y < p.y || (y == p.y && x < p.x); }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    ll operator * (point p) { return (ll)x * p.x + (ll)y * p.y; }

    int updown() { return y < 0 || (y == 0 && x > 0) ? 0 : 1;}
    db norm() { return hypot(x, y); }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
    bool on(point pa, point pb) { return ccw(pa, pb) ? false : ((*this - pa) * (*this - pb) <= 0); }
};

int T, n;
db perimeter;
point O = point(0, 0);
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool cmp(point pa, point pb) {
    if (pa.updown() != pb.updown()) { return pa.updown() < pb.updown(); }
    return (ll)pa.y * pb.x < (ll)pa.x * pb.y;
}

vector <point> Build_ConvexHull(vector <point> &p) {
    vector <point> points;
    sort(p.begin(), p.end());
    bool chk = true;
    for (int i = 0; i < p.size(); ++i) {
        if (p[0].ccw(p[1], p[i])) {
            chk = false;
            break;
        }
    }
    if (chk) {
        points = p;
        p.clear();
        return points;
    }
    for (int i = 0; i < p.size(); ++i) {
        p[i].index = i;
        p[i].joined = false;
    }
    vector <point> pts = p;
    int n = p.size(), sz = 0;
    p.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || pts[0].ccw(pts[i], pts[n - 1]) >= 0) {
            while (sz && p[sz - 1].ccw(p[sz], pts[i]) < 0) {
                sz--;
            }
            p[++sz] = pts[i];
        }
    }
    if (sz != n - 1) {
        for (int i = n - 2, j = sz; i >= 0; --i) {
            if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) >= 0) {
                while (sz > j && p[sz - 1].ccw(p[sz], pts[i]) < 0) {
                    sz--;
                }
                p[++sz] = pts[i];
            }
        }
        p.resize(sz);
    }
    else {
        p.resize(sz + 1);
    }
    for (int i = 0; i < p.size(); ++i) {
        pts[p[i].index].joined = true;
    }
    points = p;
    p.clear();
    for (auto it : pts) {
        if (!it.joined) {
            p.push_back(it);
        }
    }
    return points;
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }
        perimeter = 0;

        vector <point> pinit = p;
        p.push_back(O);
        vector <vector <point>> pp(2);
        pp[0] = Build_ConvexHull(p);
        p.push_back(O);
        pp[1] = Build_ConvexHull(p);

        if (pp[0].size() + pp[1].size() == n + 2) {
            bool chk = true;
            for (int i = 0; i < 2; ++i) {
                if (pp[i].size() < 3) {
                    chk = false;
                    break;
                }
                bool contain = false;
                int m = pp[i].size();
                for (int j = 0; j < m; ++j) {
                    if (!pp[i][j].x && !pp[i][j].y) {
                        contain = true;
                    }
                    int pre = (j - 1 + m) % m, nxt = (j + 1) % m;
                    if (!pp[i][pre].ccw(pp[i][j], pp[i][nxt])) {
                        chk = false;
                        break;
                    }
                }
                if (!contain) {
                    chk = false;
                }
                if (!chk) {
                    break;
                }
            }
            if (chk) {
                for (int i = 0; i < 2; ++i) {
                    int m = pp[i].size();
                    for (int j = 0; j < m; ++j) {
                        int nxt = (j + 1) % m;
                        perimeter += (pp[i][j] - pp[i][nxt]).norm();
                    }
                }
            }
        }

        p = pinit;
        sort(p.begin(), p.end(), cmp);
        int pos = - 1;
        bool chk = true;
        for (int i = 0; i < n; ++i) {
            int nxt = (i + 1) % n;
            if (p[i].on(O, p[nxt]) || p[nxt].on(O, p[i])) {
                chk = false;
                break;
            }
        }
        if (chk) {
            for (int i = 0; i < n; ++i) {
                int pre = (i - 1 + n) % n, nxt = (i + 1) % n;
                if (p[pre].ccw(p[i], p[nxt]) < 0 || p[i].on(p[pre], p[nxt])) {
                    p[i].isfault = true;
                }
                else {
                    p[i].isfault = false;
                }
                p[i].index = i;
            }
            vector <deque <point>> pts(2);
            vector <db> len(2, 0);
            vector <int> fault(2);
            vector <bool> status(2, true);
            pts[0].push_back(p[0]);
            for (int i = 1; i < n; ++i) {
                if (p[0].ccw(O, p[i]) < 0) {
                    len[0] += (pts[0].back() - p[i]).norm();
                    if (pts[0].size() >= 2 && pts[0].back().isfault) {
                        status[0] = false;
                        fault[0] = pts[0].back().index;
                    }
                    pts[0].push_back(p[i]);
                }
                else {
                    if (pts[1].size()) {
                        len[1] += (pts[1].back() - p[i]).norm();
                    }
                    if (pts[1].size() >= 2 && pts[1].back().isfault) {
                        status[1] = false;
                        fault[1] = pts[1].back().index;
                    }
                    pts[1].push_back(p[i]);
                }
            }
            if ((status[0] && pts[0].size() >= 2 && O.ccw(pts[0].front(), pts[0].back()) > 0) && (status[1] && pts[1].size() >= 2 && O.ccw(pts[1].front(), pts[1].back()) > 0)) {
                perimeter = max(perimeter, len[0] + (O - pts[0].front()).norm() + (O - pts[0].back()).norm() + len[1] + (O - pts[1].front()).norm() + (O - pts[1].back()).norm());
            }
            for (int i = 1; i < n; ++i) {
                point po = pts[0].front();
                if (pts[1].size()) {
                    len[1] += (pts[1].back() - po).norm();
                }
                if (pts[1].size() >= 2 && pts[1].back().isfault) {
                    status[1] = false;
                    fault[1] = pts[1].back().index;
                }
                pts[1].push_back(po);
                pts[0].pop_front();
                if (pts[0].size()) {
                    len[0] -= (pts[0].front() - po).norm();
                    if (!status[0]) {
                        if (pts[0].front().isfault && pts[0].front().index == fault[0]) {
                            status[0] = true;
                        }
                    }
                }
                else {
                    pts[0].push_back(p[i]);
                    point po = pts[1].front();
                    pts[1].pop_front();
                    if (pts[1].size()) {
                        len[1] -= (pts[1].front() - po).norm();
                        if (!status[1]) {
                            if (pts[1].front().isfault && pts[1].front().index == fault[1]) {
                                status[1] = true;
                            }
                        }
                    }
                }
                while (pts[1].size() && p[i].ccw(O, pts[1].front()) < 0) {
                    po = pts[1].front();
                    len[0] += (pts[0].back() - po).norm();
                    if (pts[0].size() >= 2 && pts[0].back().isfault) {
                        status[0] = false;
                        fault[0] = pts[0].back().index;
                    }
                    pts[0].push_back(po);
                    pts[1].pop_front();
                    if (pts[1].size()) {
                        len[1] -= (pts[1].front() - po).norm();
                        if (!status[1]) {
                            if (pts[1].front().isfault && pts[1].front().index == fault[1]) {
                                status[1] = true;
                            }
                        }
                    }
                }
                if ((status[0] && pts[0].size() >= 2 && O.ccw(pts[0].front(), pts[0].back()) > 0) && (status[1] && pts[1].size() >= 2 && O.ccw(pts[1].front(), pts[1].back()) > 0)) {
                    perimeter = max(perimeter, len[0] + (O - pts[0].front()).norm() + (O - pts[0].back()).norm() + len[1] + (O - pts[1].front()).norm() + (O - pts[1].back()).norm());
                }
            }
        }

        cout << fixed << setprecision(10) << perimeter << "\n";
    }
}

int main() {
    Task();
    Solve();
}
