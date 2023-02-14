// https://codeforces.com/gym/100491/submit

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef double db;

const db pi = acos(- 1);

struct point {
    int x, y, index;
    bool getin;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point other) {
        if (x != other.x) { return x < other.x; }
        if (getin != other.getin) { return getin == false; }
        return y < other.y;
    }
    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll norm2() { return (ll)x * x + (ll)y * y; }
};

struct circle {
    point I;
    int r, index;

    circle() {}
    circle(point pa, int i) { I = pa, r = i; }

    bool contain(circle c) { return r > c.r && (I - c.I).norm2() <= ((ll)r - c.r) * (r - c.r); }

    db area() { return pi * r * r; }
};

bool operator < (circle ca, circle cb) {
    if (ca.I.y != cb.I.y) { return ca.I.y < cb.I.y; }
    return ca.index < cb.index;
}

int n;
vector <circle> c;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("circles.in", "r", stdin);
    freopen("circles.out", "w", stdout);
}

void Solve() {
    cin >> n;
    set <pair <pair <int, int>, int>> st;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        st.insert({{a, b}, c});
    }
    for (auto i : st) {
        c.push_back(circle(point(i.first.first, i.first.second), i.second));
        c.back().index = c.size() - 1;
    }
    n = c.size();

    vector <point> p;
    for (int i = 0; i < n; ++i) {
        p.push_back(point(c[i].I.x - c[i].r, c[i].I.y));
        p.back().getin = true;
        p.back().index = i;
        p.push_back(point(c[i].I.x + c[i].r, c[i].I.y));
        p.back().getin = false;
        p.back().index = i;
    }
    sort(p.begin(), p.end());

    vector <bool> iscovered(n, false);
    tree <circle, null_type, less<circle>, rb_tree_tag, tree_order_statistics_node_update> Tree;
    for (int i = 0; i < p.size(); ++i) {
        circle curr = c[p[i].index];
        if (!p[i].getin) {
            Tree.erase(curr);
        }
        else {
            Tree.insert(curr);

            auto it = Tree.find(curr);
            while (true) {
                auto upp = it;
                upp++;
                if (upp != Tree.end() && curr.contain(*upp)) {
                    iscovered[(*upp).index] = true;
                    Tree.erase(*upp);
                }
                else {
                    break;
                }
            }
            while (true) {
                auto dow = it;
                if (dow != Tree.begin()) {
                    dow--;
                    if (curr.contain(*dow)) {
                        iscovered[(*dow).index] = true;
                        Tree.erase(*dow);
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }

            auto upp = it;
            upp++;
            circle cc = *upp;
            if (upp != Tree.end() && cc.contain(*it)) {
                iscovered[(*it).index] = true;
                Tree.erase(*it);
            }
            else {
                auto dow = it;
                if (dow != Tree.begin()) {
                    dow--;
                    cc = *dow;
                    if (cc.contain(*it)) {
                        iscovered[(*it).index] = true;
                        Tree.erase(*it);
                    }
                }
            }
        }
    }

    db area = 0;
    for (int i = 0; i < n; ++i) {
        if (!iscovered[i]) {
            area += c[i].area();
        }
    }

    cout << fixed << setprecision(10) << area;
}

int main() {
    Task();
    Solve();
}
