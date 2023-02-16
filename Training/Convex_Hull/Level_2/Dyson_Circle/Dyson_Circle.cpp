#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll a) { return a == 0 ? 0 : (a > 0 ? 1 : - 1); }

struct point {
	int x, y;

	point() {}
	point(int a, int b) { x = a, y = b; }

	bool operator < (point a) { return y != a.y ? y < a.y : x < a.x; }
	point operator - (point p) { return point(x - p.x, y - p.y); }

	int manhattan(point p) { return max(abs(x - p.x), abs(y - p.y)); }
	ll det(point p) { return (ll)x * p.y - (ll)y * p.x; }

	int ccw(point pa, point pb) { return sign((pa - *this).det(pb - *this)); }
};

int n;
ll cnt;
vector <point> p;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Build_ConvexHull(vector <point> &p) {
	sort(p.begin(), p.end());
	if (p.size() < 3) {return;}
	bool chk = true;
	for (int i = 2; i < p.size(); ++i) {
		if (p[0].ccw(p[1], p[i]) != 0) {
			chk = false;
			break;
		}
	}
	if (chk) {
		p[1] = p.back();
		p.resize(2);
		return;
	}
	vector <point> pts = p;
	int n = p.size(), sz = 0;
	p.resize(n + 1);
	for (int i = 1; i < n; ++i) {
		if (i == n - 1 || pts[0].ccw(pts[i], pts[n - 1]) > 0) {
			while (sz > 0 && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
				sz--;
			}
			p[++sz] = pts[i];
		}
	}
	for (int i = n - 2, j = sz; i >= 0; --i) {
		if (i == 0 || pts[n - 1].ccw(pts[i], pts[0]) > 0) {
			while (sz > j && p[sz - 1].ccw(p[sz], pts[i]) <= 0) {
				sz--;
			}
			p[++sz] = pts[i];
		}
	}
	p.resize(sz);
}

void Solve(){
	cin >> n;
	p.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> p[i].x >> p[i].y;
	}

	if (n == 1) {
		return void(cout << 4);
	}

	Build_ConvexHull(p);

	if (p.size() == 2 && abs(p[0].x - p[1].x) == abs(p[0].y - p[1].y)) {
		cnt = 2 * (ll)abs(p[0].x - p[1].x) + 5;
	}
	else {
		cnt = 4;
		for (int i = 0; i < p.size(); ++i) {
			int nxt = (i + 1) % p.size();
			cnt += (ll)p[i].manhattan(p[nxt]);
		}
	}

	cout << cnt;
}

int main(){
    Task();
    Solve();
}
