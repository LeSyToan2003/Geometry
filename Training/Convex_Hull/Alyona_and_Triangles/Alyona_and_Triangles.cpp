#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct point {
    int x, y;

    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator < (point p) {
        return y != p.y ? y < p.y : x < p.x;
    }

    point operator + (point p) {
        return point(x + p.x, y + p.y);
    }

    point operator - (point p) {
        return point(x - p.x, y - p.y);
    }

    ll cross(point p) {
        return (ll)x * p.y - (ll)y * p.x;
    }

    int ccw(point pa, point pb) {
        ll c = (pa - *this).cross(pb - *this);
        return !c ? 0 : (c > 0 ? 1 : - 1);
    }

    ll area(point pa, point pb) {
        return abs((pa - *this).cross(pb - *this));
    }
};

int n;
ll S;
vector <point> vecP;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void ConvexHull(vector <point> &vecP) {
    sort(vecP.begin(), vecP.end());
    int n = vecP.size(), n1 = 0;
    vector <point> vecP1 = vecP;
    vecP.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || vecP1[0].ccw(vecP1[i], vecP1[n - 1]) > 0) {
            while (n1 > 0 && vecP[n1 - 1].ccw(vecP[n1], vecP1[i]) <= 0) {
                n1--;
            }
            vecP[++n1] = vecP1[i];
        }
    }
    for (int i = n - 2, j = n1; i >= 0; --i) {
        if (!i || vecP1[n - 1].ccw(vecP1[i], vecP1[0]) > 0) {
            while (n1 > j && vecP[n1 - 1].ccw(vecP[n1], vecP1[i]) <= 0) {
                n1--;
            }
            vecP[++n1] = vecP1[i];
        }
    }
    vecP.resize(n1);
}

void Solve() {
    cin >> n >> S;
    vecP.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecP[i].x >> vecP[i].y;
    }
    ConvexHull(vecP);
    int i1 = 0, i2 = 1, i3 = 2;
    vector <int> vecA;
    ll maxx = 0;
    while (true) {
        while (true) {
            while (true) {
                int i3Next = (i3 + 1) % n;
                if (i3Next != 2 && vecP[i1].area(vecP[i2], vecP[i3]) < vecP[i1].area(vecP[i2], vecP[i3Next])) {
                    i3 = i3Next;
                } else {
                    break;
                }
            }
            int i2Next = (i2 + 1) % n;
            if (i2Next != 1 && vecP[i1].area(vecP[i2], vecP[i3]) < vecP[i1].area(vecP[i2Next], vecP[i3])) {
                i2 = i2Next;
            } else {
                break;
            }
        }
        ll area = vecP[i1].area(vecP[i2], vecP[i3]);
        if (area > maxx) {
            maxx = area;
            vecA = {i1, i2, i3};
        }
        i1 = (i1 + 1) % n;
        if (!i1) {
            break;
        }
        if (i1 == i2) {
            i2 = (i2 + 1) % n;
        }
        if (i2 == i3) {
            i3 = (i3 + 1) % n;
        }
    }
    for (int i = 0; i < 3; ++i) {
        int iNext = (i + 1) % 3, iNext2 = (i + 2) % 3;
        point p = vecP[vecA[iNext]] + vecP[vecA[iNext2]] - vecP[vecA[i]];
        cout << p.x << " " << p.y << "\n";
    }
}

int main() {
    Task();
    Solve();
}
