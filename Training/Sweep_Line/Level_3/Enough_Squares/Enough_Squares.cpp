// https://codeforces.com/gym/103577/submit

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const db eps = 1e-9;

bool eq(db a, db b) { return abs(a - b) <= eps; }
bool lt(db a, db b) { return a < b - eps; }

int sign(db a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
	db x, y, ymin, ymax;

	point() {}
	point(db a, db b) { x = a, y = b; }

	bool operator == (point p) { return eq(x, p.x) && eq(y, p.y); }
	bool operator != (point p) { return !eq(x, p.x) || !eq(y, p.y); }
	bool operator < (point p) { return lt(x, p.x) || eq(x, p.x) && lt(y, p.y); }
	point operator + (point p) { return point(x + p.x, y + p.y); }
	point operator - (point p) { return point(x - p.x, y - p.y); }
	point operator * (db k) { return point(x * k, y * k); }

	db det(point p) { return x * p.y - y * p.x; }

	int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

struct line {
    point M, N;

    line() {}
    line(point pa, point pb) { M = pa, N = pb; }

    point dir() { return M - N; }

    bool its(line l) { return l.M.ccw(M, N) != l.N.ccw(M, N); }

    point pits(line l) { return M + dir() * (l.dir().det(M - l.M) / dir().det(l.dir())); }
};

int n, w, h;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
	if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

db Area(vector <point> &p) {
	db area = 0;
	for (int i = 0; i < p.size(); ++i) {
		int nxt = (i + 1) % p.size();
		area += p[i].x * p[nxt].y - p[i].y * p[nxt].x;
	}
	return area;
}

void Killer(db &a) {
    if (eq(a, (int)a)) { a = (int)a; }
    if (eq(a, ceil(a))) { a = ceil(a); }
}

void Solve() {
	cin >> n >> w >> h;
	p.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> p[i].x >> p[i].y;
	}

	if (Area(p) < 0) {
		reverse(p.begin(), p.end());
	}

	ll cnt = 0;
	for (db x = 0.5; x < w; ++x) {
		point pa = point(x, - 1), pb = point(x, 1e5 + 1);
		vector <point> points;
		for (int i = 0; i < n; ++i) {
			int pre = (i - 1 + n) % n, nxt = (i + 1) % n, nxt2 = (i + 2) % n;
			if (line(pa, pb).its(line(p[i], p[nxt]))) {
				point pc = line(pa, pb).pits(line(p[i], p[nxt]));
				Killer(pc.y);
				if (!points.size() || (pc != points[0] && pc != points.back())) {
					db a = (p[i].y - p[nxt].y) / (p[i].x - p[nxt].x), b = p[i].y - a * p[i].x;
					pc.ymin = min(a * (x - 0.5) + b, a * (x + 0.5) + b);
					pc.ymax = max(a * (x - 0.5) + b, a * (x + 0.5) + b);
					Killer(pc.ymin);
					Killer(pc.ymax);
					bool chk = false;
					if ((!p[pre].ccw(pa, pb) && !p[i].ccw(pa, pb)) || (!p[nxt].ccw(pa, pb) && !p[nxt2].ccw(pa, pb))) {
						if (pc == p[i]) {
							if (p[pre].ccw(p[i], p[nxt]) > 0) {
								chk = true;
							}
						}
						else if (pc == p[nxt]) {
							if (p[i].ccw(p[nxt], p[nxt2]) > 0) {
								chk = true;
							}
						}
					}
					else if (pc == p[i]) {
						if (p[pre].ccw(pa, pb) != p[nxt].ccw(pa, pb)) {
							chk = true;
						}
					}
					else if (pc == p[nxt]) {
						if (p[i].ccw(pa, pb) != p[nxt2].ccw(pa, pb)) {
							chk = true;
						}
					}
					else {
						chk = true;
					}
                    if (chk) {
                        points.push_back(pc);
					}
				}
			}
		}
		sort(points.begin(), points.end());
		set <int> st;
		int curr = 0;
		for (int i = 0; i + 1 < points.size(); i += 2) {
			int dow = (int)points[i].ymin, upp = (int)points[i + 1].ymax;
			if (eq(points[i + 1].ymax, (int)points[i + 1].ymax)) {
				upp--;
			}
			if (st.size()) {
				auto it = st.end();
				it--;
				if (dow <= *it) {
					dow = *it + 1;
				}
			}
			if (dow <= upp) {
				curr += upp - dow + 1;
				st.insert(dow);
				st.insert(upp);
			}
		}
		cnt += (ll)curr;
	}

	cout << cnt;
}

int main() {
    Task();
    Solve();
}
