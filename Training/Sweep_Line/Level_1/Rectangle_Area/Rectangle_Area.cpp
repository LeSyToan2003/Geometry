#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct event {
    int x, yl, yr, val;

    event() {}
    event(int _x, int _yl, int _yr, int _val) {
        x = _x, yl = _yl, yr = _yr, val = _val;
    }

    bool operator < (event e) {
        return x < e.x;
    }
};

struct SegTree {
    vector <int> vec, val, fre;

    SegTree() {}
    SegTree(vector <int> _vec) {
        vec = _vec;
        val.assign(vec.size() * 4, 0);
        fre.assign(vec.size() * 4, 0);
    }

    void update(int id, int l, int r, int x, int y, int v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) {
            fre[id] += v;
            if (fre[id]) {
                val[id] = vec[r + 1] - vec[l];
            } else if (l != r) {
                val[id] = val[id * 2 + 1] + val[id * 2 + 2];
            } else {
                val[id] = 0;
            }
            return;
        }
        int m = (l + r) / 2;
        update(id * 2 + 1, l, m, x, y, v);
        update(id * 2 + 2, m + 1, r, x, y, v);
        if (fre[id]) {
            val[id] = vec[r + 1] - vec[l];
        } else {
            val[id] = val[id * 2 + 1] + val[id * 2 + 2];
        }
    }
};

int n, xl, yl, xr, yr;;
ll area;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    vector <event> vecE;
    set <int> setY;
    for (int i = 0; i < n; ++i) {
        cin >> xl >> yl >> xr >> yr;
        vecE.push_back(event(xl, yl, yr, 1));
        vecE.push_back(event(xr, yl, yr, - 1));
        setY.insert(yl);
        setY.insert(yr);
    }
    sort(vecE.begin(), vecE.end());
    vector <int> vecY(setY.begin(), setY.end());
    SegTree ST(vecY);
    for (int i = 0; i + 1 < vecE.size(); ++i) {
        event e = vecE[i];
        int l = lower_bound(vecY.begin(), vecY.end(), e.yl) - vecY.begin();
        int r = lower_bound(vecY.begin(), vecY.end(), e.yr) - vecY.begin() - 1;
        ST.update(0, 0, vecY.size() - 2, l, r, e.val);
        area += (ll)ST.val[0] * (vecE[i + 1].x - vecE[i].x);
    }
    cout << area;
}

int main() {
    Task();
    Solve();
}
