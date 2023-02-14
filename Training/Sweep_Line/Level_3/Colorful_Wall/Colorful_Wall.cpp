// https://codeforces.com/gym/103443/submit

#include <bits/stdc++.h>

using namespace std;

struct event {
    int val, ind, lef, rig;
    bool sta;

    event() {}
    event(int a, int b, int c, int d, bool e) { val = a; ind = b; lef = c; rig = d; sta = e; }

    bool operator < (event a) { return val < a.val; }
};

int n;
vector <bool> color;
vector <int> xx;
vector <event> yy;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
	if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n;
    vector <int> c(n);
    set <int> st;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2 >> c[i];
        c[i]--;
        st.insert(x1);
        st.insert(x2);
        yy.push_back(event(y1, i, x1, x2, false));
        yy.push_back(event(y2, i, x1, x2, true));
    }

    sort(yy.begin(), yy.end());
    for (auto i : st) {
        xx.push_back(i);
    }
    color.resize(n);
    for (int i = 0; i < n; ++i) {
        color[i] = false;
    }

    for (int i = 0; i < xx.size() - 1; ++i) {
        vector <event> curr;
        for (int j = 0; j < yy.size(); ++j) {
            if (yy[j].lef <= xx[i] && xx[i + 1] <= yy[j].rig) {
                curr.push_back(yy[j]);
            }
        }
        if (curr.size()) {
            set <int> pos;
            for (int j = 0; j < curr.size() - 1; ++j) {
                if (curr[j].sta) {
                    pos.insert(curr[j].ind);
                }
                else {
                    pos.erase(curr[j].ind);
                }
                if (pos.size() && curr[j].val != curr[j + 1].val) {
                    auto it = pos.end();
                    it--;
                    color[c[*it]] = true;
                }
            }
        }
    }

    int cnt = 0;
    for (auto i : color) {
        cnt += i;
    }

    cout << cnt;
}

int main() {
    Task();
    Solve();
}
