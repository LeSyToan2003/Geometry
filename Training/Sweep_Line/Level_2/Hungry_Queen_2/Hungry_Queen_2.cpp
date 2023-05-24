#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) {
    return !a ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y, index;
    bool status;

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

    bool canTake(point p) {
        return x == p.x || y == p.y || x + y == p.x + p.y || x - y == p.x - p.y;
    }

    ll dot(point p) {
        return (ll)x * p.x + (ll)y * p.y;
    }

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }

    bool on(point pa, point pb) {
        return ccw(pa, pb) ? false : (pa - *this).dot(pb - *this) <= 0;
    }
};

int n;
vector <point> vecP;
set <point> setP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("queen2.in", "r", stdin);
    freopen("queen2.out", "w", stdout);
}

bool operator < (point pa, point pb) {
    return pa.x != pb.x ? pa.x < pb.x : pa.y < pb.y;
}

bool cmp1(point pa, point pb) {
    return pa.x != pb.x ? pa.x < pb.x : pa.index > pb.index;
}

bool cmp2(point pa, point pb) {
    return pa.y != pb.y ? pa.y < pb.y : pa.index > pb.index;
}

bool cmp3(point pa, point pb) {
    int a = pa.x + pa.y, b = pb.x + pb.y;
    return a != b ? a < b : pa.index > pb.index;
}

bool cmp4(point pa, point pb) {
    int a = pa.x - pa.y, b = pb.x - pb.y;
    return a != b ? a < b : pa.index > pb.index;
}

bool cmp5(point pa, point pb) {
    return pa.index < pb.index;
}

set <point> :: iterator prev(set <point> :: iterator it) {
    return it == setP.begin() ? setP.end() : --it;
}

set <point> :: iterator next(set <point> :: iterator it) {
    return ++it;
}

void Processing1() {
    sort(vecP.begin(), vecP.end(), cmp1);
    for (int i = 0; i < n; ++i) {
        if (setP.empty() || (i > 0 && vecP[i - 1].x == vecP[i].x)) {
            point p = vecP[i], q = vecP[i - 1];
            setP.insert(p);
            if (setP.size() > 2 && q.index - 1 == p.index) {
                auto curr = setP.find(p);
                auto pre = prev(curr);
                auto nxt = next(curr);
                bool chk = false;
                if (pre != setP.end()) {
                    point ppre = *pre;
                    if (ppre == q) {
                        chk = true;
                    }
                }
                if (nxt != setP.end()) {
                    point pnxt = *nxt;
                    if (pnxt == q) {
                        chk = true;
                    }
                }
                if (!chk) {
                    vecP[i - 1].status = false;
                }
            }
        } else {
            setP.clear();
            setP.insert(vecP[i]);
        }
    }
}

void Processing2() {
    sort(vecP.begin(), vecP.end(), cmp2);
    for (int i = 0; i < n; ++i) {
        if (setP.empty() || (i > 0 && vecP[i - 1].y == vecP[i].y)) {
            point p = vecP[i], q = vecP[i - 1];
            setP.insert(p);
            if (setP.size() > 2 && q.index - 1 == p.index) {
                auto curr = setP.find(p);
                auto pre = prev(curr);
                auto nxt = next(curr);
                bool chk = false;
                if (pre != setP.end()) {
                    point ppre = *pre;
                    if (ppre == q) {
                        chk = true;
                    }
                }
                if (nxt != setP.end()) {
                    point pnxt = *nxt;
                    if (pnxt == q) {
                        chk = true;
                    }
                }
                if (!chk) {
                    vecP[i - 1].status = false;
                }
            }
        } else {
            setP.clear();
            setP.insert(vecP[i]);
        }
    }
}

void Processing3() {
    sort(vecP.begin(), vecP.end(), cmp3);
    for (int i = 0; i < n; ++i) {
        if (setP.empty() || (i > 0 && vecP[i - 1].x + vecP[i - 1].y == vecP[i].x + vecP[i].y)) {
            point p = vecP[i], q = vecP[i - 1];
            setP.insert(p);
            if (setP.size() > 2 && q.index - 1 == p.index) {
                auto curr = setP.find(p);
                auto pre = prev(curr);
                auto nxt = next(curr);
                bool chk = false;
                if (pre != setP.end()) {
                    point ppre = *pre;
                    if (ppre == q) {
                        chk = true;
                    }
                }
                if (nxt != setP.end()) {
                    point pnxt = *nxt;
                    if (pnxt == q) {
                        chk = true;
                    }
                }
                if (!chk) {
                    vecP[i - 1].status = false;
                }
            }
        } else {
            setP.clear();
            setP.insert(vecP[i]);
        }
    }
}

void Processing4() {
    sort(vecP.begin(), vecP.end(), cmp4);
    for (int i = 0; i < n; ++i) {
        if (setP.empty() || (i > 0 && vecP[i - 1].x - vecP[i - 1].y == vecP[i].x - vecP[i].y)) {
            point p = vecP[i], q = vecP[i - 1];
            setP.insert(p);
            if (setP.size() > 2 && q.index - 1 == p.index) {
                auto curr = setP.find(p);
                auto pre = prev(curr);
                auto nxt = next(curr);
                bool chk = false;
                if (pre != setP.end()) {
                    point ppre = *pre;
                    if (ppre == q) {
                        chk = true;
                    }
                }
                if (nxt != setP.end()) {
                    point pnxt = *nxt;
                    if (pnxt == q) {
                        chk = true;
                    }
                }
                if (!chk) {
                    vecP[i - 1].status = false;
                }
            }
        } else {
            setP.clear();
            setP.insert(vecP[i]);
        }
    }
}

void Solve() {
    cin >> n;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
        vecP[i].index = i;
        vecP[i].status = true;
    }
    point queen = point(0, 0);
    if (queen.canTake(vecP[0])) {
        for (int i = 1; i < n; ++i) {
            if (vecP[i].on(queen, vecP[0])) {
                return void(cout << 0);
            }
        }
    } else {
        return void(cout << 0);
    }
    Processing1();
    Processing2();
    Processing3();
    Processing4();
    sort(vecP.begin(), vecP.end(), cmp5);
    for (int i = 0; i < n; ++i) {
        if (vecP[i].status && queen.canTake(vecP[i])) {
            queen = vecP[i];
        } else {
            return void(cout << i);
        }
    }
    cout << n;
}

int main() {
    Task();
    Solve();
}

