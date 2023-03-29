#include <bits/stdc++.h>

using namespace std;

struct event {
    int y, xl, xr, color, order, val;

    event() {}
    event(int _y, int _xl, int _xr, int _order, int _val) {
        y = _y, xl = _xl, xr = _xr, order = _order, val = _val;
    }

    bool operator < (event ev) {
        return y < ev.y;
    }
};

int n, xl, yl, xr, yr, cnt;
vector <bool> status;
vector <int> color;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    status.assign(n, false);
    color.resize(n);
    vector <int> vecX;
    vector <event> vecEv;
    for (int i = 0; i < n; ++i) {
        cin >> xl >> yr >> xr >> yl >> color[i];
        color[i]--;
        vecX.push_back(xl);
        vecX.push_back(xr);
        vecEv.push_back(event(yl, xl, xr, i, 1));
        vecEv.push_back(event(yr, xl, xr, i, - 1));
    }
    sort(vecX.begin(), vecX.end());
    sort(vecEv.begin(), vecEv.end());
    vecX.erase(unique(vecX.begin(), vecX.end()), vecX.end());
    for (auto x : vecX) {
        vector <event> vec;
        for (auto ev : vecEv) {
            if (ev.xl <= x && ev.xr > x) {
                vec.push_back(ev);
            }
        }
        if (vec.empty()) continue;
        set <int> setO;
        for (int i = 0; i + 1 < vec.size(); ++i) {
            if (vec[i].val == 1) {
                setO.insert(vec[i].order);
            } else {
                setO.erase(vec[i].order);
            }
            if (vec[i].y != vec[i + 1].y && !setO.empty()) {
                auto it = setO.end();
                it--;
                status[color[*it]] = true;
            }
        }
    }
    cnt = accumulate(status.begin(), status.end(), 0);
    cout << cnt;
}

int main() {
    Task();
    Solve();
}
