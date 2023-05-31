#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int inf = 1e9 + 9;
const ld eps = 1e-9;

bool eq(ld a, ld b) {
    return abs(a - b) <= eps;
}

int sign(ll a) {
    return !a ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y, x1, y1, x2, y2, index;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
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
    point M, N;
    int index;

    line() {}
    line(point _M, point _N) {
        M = _M, N = _N;
    }

    ld its(ld x) {
        return (x * (N.y - M.y) + (ld)M.y * N.x - (ld)M.x * N.y) / (ld)(N.x - M.x);
    }
};

int n, k, x, diameter, node1, node2, root;
vector <int> vecPar, vecDist;
vector <point> vecP;
vector <vector <int>> vecEdge;
set <line> setL;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (line la, line lb) {
    ld a = la.its(x), b = lb.its(x);
    if (!eq(a, b)) {
        return a < b;
    }
    ld xx = (max(la.M.x, lb.N.x) + min(la.N.x, lb.M.x)) / 2.0;
    return la.its(xx) < lb.its(xx);
}

set <line> :: iterator next(line l) {
    return setL.upper_bound(l);
}

void DFS(int u, int d, int par) {
    if (d > diameter) {
        diameter = d;
        node1 = u;
    }
    vecDist[u] = d;
    for (auto v : vecEdge[u]) {
        if (v != par) {
            DFS(v, d + 1, u);
        }
    }
}

int Processing() {
    vecEdge.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        vecEdge[i].push_back(vecPar[i]);
        vecEdge[vecPar[i]].push_back(i);
    }
    vecDist.resize(n + 1);
    DFS(root, 0, - 1);
    vector <int> vecD = vecDist;
    node2 = node1;
    DFS(node2, 0, - 1);
    return diameter + max(vecD[node1], vecD[node2]);
}

void Solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> k;
        vector <point> vecPts(k);
        for (int j = 0; j < k; ++j) {
            cin >> vecPts[j].x >> vecPts[j].y;
            vecPts[j].index = i;
        }
        for (int j = 0; j < k; ++j) {
            int jj = (j - 1 + k) % k, jjj = (j + 1) % k;
            vecPts[j].x1 = vecPts[jj].x, vecPts[j].y1 = vecPts[jj].y;
            vecPts[j].x2 = vecPts[jjj].x, vecPts[j].y2 = vecPts[jjj].y;
            vecP.push_back(vecPts[j]);
        }
    }
    sort(vecP.begin(), vecP.end());
    vecPar.assign(n, - 1);
    root = n;
    for (int i = 0; i < vecP.size(); ++i) {
        x = vecP[i].x;
        int node = vecP[i].index;
        if (vecPar[node] == - 1) {
            line l = line(point(- inf, vecP[i].y), point(inf, vecP[i].y));
            auto nxt = next(l);
            if (nxt == setL.end()) {
                vecPar[node] = root;
            } else {
                point pa = (*nxt).M, pb = (*nxt).N;
                if (vecP[i].ccw(pa, pb) > 0) {
                    vecPar[node] = (*nxt).index;
                }
                else {
                    vecPar[node] = vecPar[(*nxt).index];
                }
            }
        }
        point pa = point(vecP[i].x1, vecP[i].y1), pb = point(vecP[i].x2, vecP[i].y2);
        line la = line(pa, vecP[i]), lb = line(vecP[i], pb);
        if (pa.x < vecP[i].x) {
            setL.erase(la);
        }
        if (pb.x < vecP[i].x) {
            setL.erase(lb);
        }
        if (vecP[i].x < pa.x) {
            la.index = node;
            setL.insert(la);
        }
        if (vecP[i].x < pb.x) {
            lb.index = node;
            setL.insert(lb);
        }
    }
    cout << Processing();
}

int main() {
    Task();
    Solve();
}
