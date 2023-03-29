#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld pi = acos(- 1);

struct circle {
    int x, y, r, id;

    circle() {}
    circle(int _x, int _y, int _r) {
        x = _x, y = _y, r = _r;
    }

    bool contain(circle c) {
        return 1LL * (x - c.x) * (x - c.x) + 1LL * (y - c.y) * (y - c.y) <= 1LL * r * r;
    }
};

struct event {
    int x, r, id, val;

    event() {}
    event(int _x, int _r, int _id, int _val) {
        x = _x, r = _r, id = _id, val = _val;
    }

    bool operator < (event ev) {
        return x != ev.x ? x < ev.x : (val != ev.val ? val < ev.val : x + r > ev.x + ev.r);
    }
};

int n;
ld area;
vector <circle> vecC;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool operator < (circle a, circle b) {
    return a.y != b.y ? a.y < b.y : a.id < b.id;
}

void Solve() {
    cin >> n;
    vecC.resize(n);
    vector <ld> vecA(n);
    vector <event> vecEv;
    for (int i = 0; i < n; ++i) {
        cin >> vecC[i].x >> vecC[i].y >> vecC[i].r;
        vecC[i].id = i;
        vecA[i] = pi * vecC[i].r * vecC[i].r;
        vecEv.push_back(event(vecC[i].x - vecC[i].r, vecC[i].r, i, 1));
        vecEv.push_back(event(vecC[i].x + vecC[i].r, vecC[i].r, i, - 1));
    }
    sort(vecEv.begin(), vecEv.end());
    set <circle> setC;
    for (int i = 0; i < vecEv.size(); ++i) {
        if (vecEv[i].val == 1) {
            bool chk = true;
            if (!setC.empty()) {
                setC.insert(vecC[vecEv[i].id]);
                auto it = setC.find(vecC[vecEv[i].id]);
                it++;
                if (it != setC.end()) {
                    circle c = *it;
                    if (c.contain(vecC[vecEv[i].id])) {
                        chk = false;
                    }
                }
                it--;
                if (it != setC.begin()) {
                    it--;
                    circle c = *it;
                    if (c.contain(vecC[vecEv[i].id])) {
                        chk = false;
                    }
                }
                setC.erase(vecC[vecEv[i].id]);
            }
            if (!chk) {
                vecA[vecEv[i].id] = 0;
            } else {
                setC.insert(vecC[vecEv[i].id]);
            }
        } else if (vecA[vecEv[i].id]) {
            setC.erase(vecC[vecEv[i].id]);
        }
    }
    area = accumulate(vecA.begin(), vecA.end(), 0.0);
    cout << fixed << setprecision(10) << area;
}

int main() {
    Task();
    Solve();
}
