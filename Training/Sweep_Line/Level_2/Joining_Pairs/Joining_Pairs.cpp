// https://codeforces.com/gym/103640/submit

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
    int x, y, index;
    bool getin;

    point() {}
    point(int a, int b) { x = a, y = b; }

    bool operator < (point p) { return x != p.x ? x < p.x : y < p.y; }
    point operator - (point p) { return point(x - p.x, y - p.y); }

    ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

    int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

struct line {
    point M, N;
    int index;

    line() {}
    line(point a, point b, int c) { M = a, N = b, index = c; }

    bool its(line l) { return M.ccw(l.M, l.N) != N.ccw(l.M, l.N) && l.M.ccw(M, N) != l.N.ccw(M, N); }
};

bool operator < (line la, line lb) {
    int mina = min(la.M.y, la.N.y), minb = min(lb.M.y, lb.N.y);
    if (mina != minb) { return mina < minb; }
    return la.index < lb.index;
}

int w, h, n;
vector <line> l;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
	cin >> w >> h >> n;
	for (int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if ((x1 == 0 || x1 == w || y1 == 0 || y1 == h) && (x2 == 0 || x2 == w || y2 == 0 || y2 == h)) {
			if (x2 < x1 || (x2 == x1 && y2 < y1)) {
				swap(x1, x2);
				swap(y1, y2);
			}
			point pa = point(x1, y1), pb = point(x2, y2);
			pa.index = l.size(), pb.index = l.size();
			l.push_back(line(pa, pb, l.size()));
		}
	}

	if (l.size() == 0) {
        return void(cout << "Y");
	}

    vector <point> points;
    for (int i = 0; i < l.size(); ++i) {
        points.push_back(l[i].M);
        points.back().getin = true;
        points.push_back(l[i].N);
        points.back().getin = false;
    }
    sort(points.begin(), points.end());

    tree <line, null_type, less<line>, rb_tree_tag, tree_order_statistics_node_update> Tree;
    bool chk = true;
    for (int i = 0; i < points.size(); ++i) {
        line curr = l[points[i].index];
        if (points[i].getin) {
            Tree.insert(curr);
            auto it = Tree.find(curr);
            auto upp = it;
            upp++;
            if (upp != Tree.end()) {
                if (curr.its(*upp)) {
                    chk = false;
                    break;
                }
                upp++;
                if (upp != Tree.end()) {
                    if (curr.its(*upp)) {
                        chk = false;
                        break;
                    }
                }
            }
            auto dow = it;
            if (dow != Tree.begin()) {
                dow--;
                if (curr.its(*dow)) {
                    chk = false;
                    break;
                }
                if (dow != Tree.begin()) {
                    dow--;
                    if (curr.its(*dow)) {
                        chk = false;
                        break;
                    }
                }
            }
        }
        else {
            auto it = Tree.find(curr);
            auto upp = it;
            upp++;
            auto dow = it;
            if (dow != Tree.begin() && upp != Tree.end()) {
                dow--;
                line li = *dow;
                if (li.its(*upp)) {
                    chk = false;
                    break;
                }
            }
            Tree.erase(curr);
        }
    }

    cout << chk ? "Y" : "N";
}

int main() {
    Task();
    Solve();
}
