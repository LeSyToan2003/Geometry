#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct event {
    int x, y1, y2, value;

    event() {}
    event(int _x, int _y1, int _y2, int _value) {
        x = _x, y1 = _y1, y2 = _y2, value = _value;
    }

    bool operator < (event e) {
        return x < e.x;
    }
};

struct segmenttree {
    int n;
    vector <int> vecData, vecValue, vecStatus;

    segmenttree() {}
    segmenttree(vector <int> &_vecData) {
        vecData = _vecData;
        n = vecData.size();
        vecValue.resize(n * 4), vecStatus.resize(n * 4);
    }

    void update(int id, int l, int r, int i, int j, int value) {
        if (j < l || i > r) {
            return;
        }
        if (i <= l && r <= j) {
            vecStatus[id] += value;
            if (vecStatus[id]) {
                vecValue[id] = vecData[r + 1] - vecData[l];
            } else if (l != r) {
                vecValue[id] = vecValue[id * 2 + 1] + vecValue[id * 2 + 2];
            } else {
                vecValue[id] = 0;
            }
            return;
        }
        int m = (l + r) / 2;
        update(id * 2 + 1, l, m, i, j, value);
        update(id * 2 + 2, m + 1, r, i, j, value);
        if (vecStatus[id]) {
            vecValue[id] = vecData[r + 1] - vecData[l];
        } else {
            vecValue[id] = vecValue[id * 2 + 1] + vecValue[id * 2 + 2];
        }
    }
};

int n;

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
    vector <event> vecEvent;
    while (n--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) continue;
        vecY.push_back(y1);
        vecY.push_back(y2);
        vecEvent.push_back(event(x1, y1, y2, 1));
        vecEvent.push_back(event(x2, y1, y2, - 1));
    }
    sort(vecEvent.begin(), vecEvent.end());
    sort(vecY.begin(), vecY.end());
    vecY.erase(unique(vecY.begin(), vecY.end()), vecY.end());
    segmenttree stArea(vecY);
    int nY = vecY.size();
    ll ans = 0;
    for (int i = 0; i + 1 < vecEvent.size(); ++i) {
        int l = lower_bound(vecY.begin(), vecY.end(), vecEvent[i].y1) - vecY.begin();
        int r = lower_bound(vecY.begin(), vecY.end(), vecEvent[i].y2) - vecY.begin() - 1;
        stArea.update(0, 0, nY - 2, l, r, vecEvent[i].value);
        ans += (ll)stArea.vecValue[0] * (vecEvent[i + 1].x - vecEvent[i].x);
    }
    cout << ans;
}

int main() {
    Task();
    Solve();
}
