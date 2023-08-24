#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct point {
    int x, y, index;

    bool operator < (point p) {
        return x < p.x;
    }
};

struct line {
    int a, b, index;

    bool operator < (line l) {
        return a != l.a ? a < l.a : b > l.b;
    }
};

struct cht {
    int it;
    vector <line> vecL;

    void update(line l) {
        while (vecL.size() > 1) {
            line l1 = vecL[vecL.size() - 1], l2 = vecL[vecL.size() - 2];
            if (1LL * (l2.b - l.b) * (l1.a - l2.a) <= 1LL * (l2.b - l1.b) * (l.a - l2.a)) {
                vecL.pop_back();
            } else {
                break;
            }
        }
        if (vecL.empty() || l.a != vecL.back().a) {
            vecL.push_back(l);
        }
    }

    ll query(int x) {
        while (it + 1 < vecL.size() && (ll)x * (vecL[it + 1].a - vecL[it].a) > vecL[it].b - vecL[it + 1].b) {
            it++;
        }
        return (ll)vecL[it].a * x + (ll)vecL[it].b;
    }
};

struct segmenttree {
    int n;
    vector <cht> vecCHT;

    segmenttree() {}
    segmenttree(int _n) {
        n = _n;
        vecCHT.resize(n * 4);
    }

    void update(int id, int l, int r, line li) {
        if (li.index < l || li.index > r) {
            return;
        }
        vecCHT[id].update(li);
        if (l == r) {
            return;
        }
        int m = (l + r) / 2;
        update(id * 2 + 1, l, m, li);
        update(id * 2 + 2, m + 1, r, li);
    }

    int query(int id, int l, int r, point p) {
        if (l == r) {
            return vecCHT[id].query(p.x) > p.y ? vecCHT[id].vecL[0].index : - 1;
        }
        int m = (l + r) / 2;
        if (vecCHT[id * 2 + 1].query(p.x) > p.y) {
            return query(id * 2 + 1, l, m, p);
        }
        if (vecCHT[id * 2 + 2].query(p.x) > p.y) {
            return query(id * 2 + 2, m + 1, r, p);
        }
        return - 1;
    }
};

int T, P;
vector <point> vecP;
vector <line> vecL;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> T;
    vecP.resize(T);
    for (int i = 0; i < T; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
        vecP[i].index = i;
    }
    cin >> P;
    vecL.resize(P);
    for (int i = 0; i < P; ++i) {
        cin >> vecL[i].a >> vecL[i].b;
        vecL[i].index = i;
    }
    sort(vecP.begin(), vecP.end());
    sort(vecL.begin(), vecL.end());
    segmenttree stLine(P);
    for (auto l : vecL) {
        stLine.update(0, 0, P - 1, l);
    }
    vector <vector <int>> vecAns(P);
    for (auto p : vecP) {
        int pos = stLine.query(0, 0, P - 1, p);
        if (pos != - 1) {
            vecAns[pos].push_back(p.index + 1);
        }
    }
    for (int i = 0; i < P; ++i) {
        sort(vecAns[i].begin(), vecAns[i].end());
        cout << vecAns[i].size() << " ";
        for (auto j : vecAns[i]) {
            cout << j << " ";
        }
        cout << "\n";
    }
}

int main() {
    Task();
    Solve();
}
