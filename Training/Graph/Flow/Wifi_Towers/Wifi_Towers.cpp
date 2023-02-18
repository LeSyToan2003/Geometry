#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct point {
    int x, y, r, s;
    bool visited;

    point() {}
    point(int a, int b) { x = a, y = b; }

    point operator - (point p) { return point(x - p.x, y - p.y); }

    int norm2() { return x * x + y * y; }

    bool inc(point p, int r) { return (*this - p).norm2() <= r * r;}
};

struct MaximumFlow {
    int timer;
    vector<int> dist, visited;
    vector<vector<int>> adj;
    vector<vector<int>> capa, flow;

    MaximumFlow() {}
    MaximumFlow(size_t sz) {
        timer = 0;
        dist.assign(sz + 1, 0);
        visited.assign(sz + 1, 0);
        adj.assign(sz + 1, vector<int>());
        capa.assign(sz + 1, vector<int>(sz + 1, 0));
        flow.assign(sz + 1, vector<int>(sz + 1, 0));
    }

    void add_edge(int u, int v, int capa) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        this->capa[u][v] += capa;
    }

    bool bfs(int s, int t) {
        fill(dist.begin(), dist.end(), 0);
        dist[s] = 1;
        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            if (u == t) { return true; }
            for (int &v: adj[u])
                if (dist[v] == 0 && capa[u][v] > flow[u][v]) {
                    dist[v] = dist[u] + 1;
                    Q.push(v);
                }
        }
        return false;
    }

    int dfs(int u, int t, int curFlow) {
        if (u == t) { return curFlow; }
        if (visited[u] == timer) { return 0; }
        else { visited[u] = timer; }
        for (int &v: adj[u]) {
            if (dist[v] == dist[u] + 1 && capa[u][v] > flow[u][v]) {
                int f = dfs(v, t, min(curFlow, capa[u][v] - flow[u][v]));
                if (f == 0) { continue; }
                flow[u][v] += f;
                flow[v][u] -= f;
                return f;
            }
        }
        return 0;
    }

    int get(int s, int t) {
        int maximumFlow = 0;
        while (bfs(s, t)) {
            while (int x = (timer++, dfs(s, t, INF))) {
                maximumFlow += x;
            }
        }
        return maximumFlow;
    }
};

int n, score;
vector <point> p;
MaximumFlow F;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y >> p[i].r >> p[i].s;
    }

    F = MaximumFlow(n + 9);
    for (int i = 0; i < n; ++i) {
        if (p[i].s >= 0) {
            F.add_edge(0, i + 1, p[i].s);
        }
        else {
            F.add_edge(i + 1, n + 1, - p[i].s);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && p[j].inc(p[i], p[i].r)) {
                F.add_edge(i + 1, j + 1, INF);
            }
        }
    }

    score = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i].s > 0) {
            score += p[i].s;
        }
    }
    score -= F.get(0, n + 1);

    cout << score;
}

int main() {
    Task();
    Solve();
}
