#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct event {
    int x, yl, yr, val;

    event() {}
    event(int _x, int _yl, int _yr, int _val) {
        x = _x, yl = _yl, yr = _yr, val = _val;
    }

    bool operator < (event ev) {
        return x < ev.x;
    }
};

struct SegTree {
    vector <int> vec, even, odd, lazy;
    vector <pair <int, int>> minv;

    SegTree() {}
    SegTree(vector <int> _vec) {
        vec = _vec;
        even.resize(vec.size() * 4), odd.resize(vec.size() * 4);
        lazy.assign(vec.size() * 4, 0), minv.assign(vec.size() * 4, {0, 0});
        build(0, 0, vec.size() - 2);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            even[id] = minv[id].second = vec[r + 1] - vec[l];
            odd[id] = 0;
            return;
        }
        int m = (l + r) / 2;
        build(id * 2 + 1, l, m);
        build(id * 2 + 2, m + 1, r);
        even[id] = minv[id].second = even[id * 2 + 1] + even[id * 2 + 2];
        odd[id] = 0;
    }

    void down(int id) {
        lazy[id * 2 + 1] += lazy[id];
        lazy[id * 2 + 2] += lazy[id];
        minv[id * 2 + 1].first += lazy[id];
        minv[id * 2 + 2].first += lazy[id];
        if (abs(lazy[id]) % 2) {
            swap(even[id * 2 + 1], odd[id * 2 + 1]);
            swap(even[id * 2 + 2], odd[id * 2 + 2]);
        }
        lazy[id] = 0;
    }

    void update(int id, int l, int r, int x, int y, int v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) {
            lazy[id] += v;
            minv[id].first += v;
            swap(even[id], odd[id]);
            return;
        }
        down(id);
        int m = (l + r) / 2;
        update(id * 2 + 1, l, m, x, y, v);
        update(id * 2 + 2, m + 1, r, x, y, v);
        even[id] = even[id * 2 + 1] + even[id * 2 + 2];
        odd[id] = odd[id * 2 + 1] + odd[id * 2 + 2];
        minv[id] = min(minv[id * 2 + 1], minv[id * 2 + 2]);
        if (minv[id * 2 + 1].first == minv[id * 2 + 2].first) {
            minv[id].second = minv[id * 2 + 1].second + minv[id * 2 + 2].second;
        }
    }
};

int n, xl, yl, xr, yr;
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
    vector <int> vecY;
    vector <event> vecEv;
    while (n--) {
        cin >> xl >> yl >> xr >> yr;
        if (xl == xr || yl == yr) continue;
        if (xl > xr) swap(xl, xr);
        if (yl > yr) swap(yl, yr);
        vecEv.push_back(event(xl, yl, yr, 1));
        vecEv.push_back(event(xr, yl, yr, - 1));
        vecY.push_back(yl);
        vecY.push_back(yr);
    }
    if (vecEv.empty()) return void(cout << 0);
    sort(vecEv.begin(), vecEv.end());
    sort(vecY.begin(), vecY.end());
    vecY.erase(unique(vecY.begin(), vecY.end()), vecY.end());
    SegTree ST(vecY);
    for (int i = 0; i + 1 < vecEv.size(); ++i) {
        int l = distance(vecY.begin(), lower_bound(vecY.begin(), vecY.end(), vecEv[i].yl));
        int r = distance(vecY.begin(), lower_bound(vecY.begin(), vecY.end(), vecEv[i].yr)) - 1;
        ST.update(0, 0, vecY.size() - 2, l, r, vecEv[i].val);
        if (!ST.minv[0].first) {
            area += 1LL * (ST.even[0] - ST.minv[0].second) * (vecEv[i + 1].x - vecEv[i].x);
        } else {
            area += 1LL * ST.even[0] * (vecEv[i + 1].x - vecEv[i].x);
        }
    }
    cout << area;
}

int main() {
    Task();
    Solve();
}
