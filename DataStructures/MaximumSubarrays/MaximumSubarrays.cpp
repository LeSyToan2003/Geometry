#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MIN = - 1E18 - 9;
const ll MAX = 1E18 + 9;

struct Node {
    ll left, right, opt;

    Node() {}
    Node(ll _left, ll _right, ll _opt) {
        left = _left, right = _right, opt = _opt;
    }

    Node operator + (Node node) {
        Node ans;
        ans.left = min(left, node.left);
        ans.right = max(right, node.right);
        ans.opt = max({opt, node.opt, node.right - left});
        return ans;
    }
};

struct SegTree {
    vector <ll> a, presum;
    vector <Node> nodes;

    SegTree() {}
    SegTree(vector <ll> &_a, vector <ll> &_presum) {
        a = _a, presum = _presum;
        int n = a.size() - 1;
        nodes.resize(n * 4);
        build(0, 1, n);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            nodes[id] = Node(presum[l - 1], presum[r], a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(id * 2 + 1, l, m);
        build(id * 2 + 2, m + 1, r);
        nodes[id] = nodes[id * 2 + 1] + nodes[id * 2 + 2];
    }

    Node query(int id, int l, int r, int from, int to) {
        if (from > r || to < l) {
            return Node(MAX, MIN, MIN);
        }
        if (from <= l && r <= to) {
            return nodes[id];
        }
        int m = (l + r) / 2;
        return query(id * 2 + 1, l, m, from, to) + query(id * 2 + 2, m + 1, r, from, to);
    }
};

void Task() {
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    int n; cin >> n;

    vector <ll> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector <ll> presum(n + 1);
    presum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        presum[i] = presum[i - 1] + a[i];
    }

    SegTree ST(a, presum);

    int m; cin >> m;

    while (m--) {
        int x, y; cin >> x >> y;

        ll ans = ST.query(0, 1, n, x, y).opt;
        cout << ans << "\n";
    }
}

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    Task();
    Solve();
}
