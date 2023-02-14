// https://oj.vnoi.info/problem/area/submit

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXD = 3e4;

struct event {
    int x, y1, y2, type;

    event() {}
    event(int a, int b, int c, int d) { x = a; y1 = b; y2 = c; type = d; }

    bool operator < (event e) { return x < e.x; }
};

struct SegmentTree {
    vector <pair <int, int>> Tree;

    SegmentTree() {}
    SegmentTree(int n) {
        Tree.resize(n * 4);
        for (int i = 0; i < n * 4; ++i) { Tree[i] = {0, 0}; }
    }

    void update(int id, int l, int r, int x, int y, int z) {
        if (x > r || y < l) { return; }
        if (x <= l && r <= y) {
            Tree[id].second += z;
            if (Tree[id].second != 0) { Tree[id].first = r - l + 1; }
            else if (l != r) { Tree[id].first = Tree[id * 2 + 1].first + Tree[id * 2 + 2].first; }
            else { Tree[id].first = 0; }
            return;
        }
        int m = (l + r) / 2;
        update(id * 2 + 1, l, m, x, y, z);
        update(id * 2 + 2, m + 1, r, x, y, z);
        if (Tree[id].second != 0) { Tree[id].first = r - l + 1; }
        else { Tree[id].first = Tree[id * 2 + 1].first + Tree[id * 2 + 2].first; }
    }
};

int n;
vector <event> e;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        e.push_back(event(x1, y1, y2, 1));
        e.push_back(event(x2, y1, y2, - 1));
    }

    sort(e.begin(), e.end());
    SegmentTree T(MAXD);

    ll area = 0;
    for (int i = 0; i + 1 < e.size(); ++i) {
        T.update(0, 0, MAXD - 1, e[i].y1, e[i].y2 - 1, e[i].type);
        area += (ll)T.Tree[0].first * (e[i + 1].x - e[i].x);
    }

    cout << area;
}

int main() {
    Task();
    Solve();
}
