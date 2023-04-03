#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

int sign(ll a) {
    return a == 0 ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator == (point p) {
        return x == p.x && y == p.y;
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

struct segment {
    point M, N;

    segment() {}
    segment(point _M, point _N) {
        M = _M, N = _N;
        if (M.x > N.x || (M.x == N.x && M.y > N.y)) swap(M, N);
    }

    ld gety(ld x) {
        if (M.x == N.x) return M.y;
        ld slope = ((ld)N.y - (ld)M.y) / ((ld)N.x - (ld)M.x);
        return (ld)M.y + slope * (x - (ld)M.x);
    }

    bool its(segment s) {
        if (M == s.M || M == s.N || N == s.M || N == s.N) return false;
        return M.ccw(s.M, s.N) != N.ccw(s.M, s.N) && s.M.ccw(M, N) != s.N.ccw(M, N);
    }
};

struct event {
    int x, tp, id;

    event() {}
    event(int _x, int _tp, int _id) {
        x = _x, tp = _tp, id = _id;
    }

    bool operator < (event e) {
        return x != e.x ? x < e.x : tp < e.tp;
    }
};

int n;
vector <point> vecP;
set <segment> setS;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (segment a, segment b) {
    ld x = ((ld)max(a.M.x, b.M.x) + (ld)min(a.N.x, b.N.x)) / 2.0;
    return a.gety(x) < b.gety(x);
}

set <segment> :: iterator prev(set <segment> :: iterator it) {
    return it == setS.begin() ? setS.end() : --it;
}

set <segment> :: iterator next(set <segment> :: iterator it) {
    return it++;
}

void solve() {
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    vector <segment> vecS(n);
    vector <event> vecE;
    map <pair <int, int>, int> mapXY;
    for (int i = 0; i < n; ++i) {
        mapXY[{vecP[i].x, vecP[i].y}]++;
        if (mapXY[{vecP[i].x, vecP[i].y}] == 2) return void(cout << "NO\n");
        int ii = (i + 1) % n;
        vecS[i] = segment(vecP[i], vecP[ii]);
        vecE.push_back(event(vecS[i].M.x, 1, i));
        vecE.push_back(event(vecS[i].N.x, - 1, i));
    }
    sort(vecE.begin(), vecE.end());
    setS.clear();
    for (int i = 0; i < vecE.size(); ++i) {
        event e = vecE[i];
        segment s = vecS[e.id];
        if (e.tp == 1) {
            if (!setS.empty()) {
                auto nxt = setS.lower_bound(s);
                auto pre = prev(nxt);
                segment snxt = *nxt;
                segment spre = *pre;
                if (nxt != setS.end() && snxt.its(s)) return void(cout << "NO\n");
                if (pre != setS.end() && spre.its(s)) return void(cout << "NO\n");
            }
            setS.insert(s);
        } else {
            auto curr = setS.find(s);
            auto nxt = next(curr);
            auto pre = prev(curr);
            segment snxt = *nxt;
            segment spre = *pre;
            if (nxt != setS.end() && pre != setS.end() && snxt.its(spre)) return void(cout << "NO\n");
            setS.erase(s);
        }
    }
    cout << "YES\n";
}

void Solve() {
    while (cin >> n && n) {
        solve();
    }
}

int main() {
    Task();
    Solve();
}
