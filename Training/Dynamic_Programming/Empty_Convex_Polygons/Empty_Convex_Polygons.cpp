#include <bits/stdc++.h>

using namespace std;

int sign(int a) {
    return !a ? 0 : (a > 0 ? 1 : - 1);
}

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator < (point p) {
        return y != p.y ? y < p.y : x < p.x;
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    int norm2() {
        return x * x + y * y;
    }

    int dot(point p) {
        return x * p.x + y * p.y;
    }

    int cross(point p) {
        return x * p.y - y * p.x;
    }

    int ccw(point pa, point pb) {
        return sign((pa - *this).cross(pb - *this));
    }

    bool on(point pa, point pb) {
        return !ccw(pa, pb) && (pa - *this).dot(pb - *this) <= 0;
    }

    int area(point pa, point pb) {
        return abs((pa - *this).cross(pb - *this));
    }

    bool inSimplePolygon(vector <point> &vecP) {
        int n = vecP.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            int iNext = (i + 1) % n;
            point pa = vecP[i], pb = vecP[iNext];
            if (on(pa, pb)) {
                return false;
            }
            if (pa.y > pb.y) {
                swap(pa, pb);
            }
            if (pa.y <= y && y < pb.y && ccw(pa, pb) < 0) {
                cnt++;
            }
        }
        return cnt % 2;
    }
};

int T, n;
point center;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

bool cmp(point pa, point pb) {
    point pc = pa - center, pd = pb - center;
    return pc.y * pd.x != pc.x * pd.y ? pc.y * pd.x < pc.x * pd.y : pc.norm2() < pd.norm2();
}

void Solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        vecP.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> vecP[i].x >> vecP[i].y;
        }
        sort(vecP.begin() + 1, vecP.end());
        vector <point> vecP1 = vecP;
        int ans = 0;
        for (int left = 1; left <= n; ++left) {
            vecP = vecP1;
            center = vecP[left];
            sort(vecP.begin() + left + 1, vecP.end(), cmp);
            vector <vector <bool>> vecValid(n + 1, vector <bool> (n + 1, true));
            vector <vector <int>> vecDP(n + 1, vector <int> (n + 1, 0));
            for (int i = left + 1; i <= n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    vector <point> vecP2 = {vecP[left], vecP[i], vecP[j]};
                    for (int k = 1; k <= n; ++k) {
                        if (vecP[k].inSimplePolygon(vecP2)) {
                            vecValid[i][j] = false;
                            break;
                        }
                    }
                }
            }
            for (int j = left + 1; j <= n; ++j) {
                for (int i = left + 1; i < j; ++i) {
                    if (!vecValid[i][j]) {
                        continue;
                    }
                    int area = vecP[left].area(vecP[i], vecP[j]);
                    vecDP[i][j] = area;
                    if (i >= left + 2 && !vecP[left].ccw(vecP[i - 1], vecP[i])) {
                        ans = max(ans, vecDP[i][j]);
                        continue;
                    }
                    for (int k = left + 1; k < i; ++k) {
                        if (vecP[k].ccw(vecP[i], vecP[j]) >= 0) {
                            vecDP[i][j] = max(vecDP[i][j], vecDP[k][i] + area);
                        }
                    }
                    ans = max(ans, vecDP[i][j]);
                }
            }
        }
        cout << fixed << setprecision(1) << ans / 2.0 << "\n";
    }
}

int main() {
    Task();
    Solve();
}
