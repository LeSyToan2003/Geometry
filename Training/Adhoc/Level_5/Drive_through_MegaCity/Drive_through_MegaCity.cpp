#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, xa, ya, xb, yb;
ll mind;
vector <int> vecX1, vecY1, vecX2, vecY2, vecX, vecY;
vector <ll> vecT;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("drive.in", "r", stdin);
    freopen("drive.out", "w", stdout);
}

void Processing() {
    if (xa > xb) {
        swap(xa, xb), swap(ya, yb);
    }
    int m = vecY.size();
    vector <ll> vecDist, vecD;
    vector <vector <ll>> vecTime(m);
    for (int i = 0; i < m; ++i) {
        vecTime[i].assign(4, 10);
    }
    for (int i = 0; i < vecX.size(); ++i) {
        vecDist.assign(m, 1e18);
        if (xa == i) {
            vecDist[ya] = 0;
        }
        if (i != 0) {
            for (int j = 0; j < m; ++j) {
                vecDist[j] = min(vecDist[j], vecD[j] + vecTime[j][1] * (vecX[i] - vecX[i - 1]));
            }
        }
        for (int j = 0; j < n; ++j) {
            if (i == vecX1[j]) {
                for (int k = vecY1[j] + 1; k < vecY2[j]; ++k) {
                    vecTime[k][1] = vecT[j];
                }
            } else if (i == vecX2[j]) {
                for (int k = vecY1[j]; k <= vecY2[j]; ++k) {
                    if (vecY1[j] < k && k < vecY2[j]) {
                        vecTime[k][1] = 10;
                    }
                    if (k < vecY2[j]) {
                        vecTime[k][0] = 10;
                    }
                    if (k > vecY1[j]) {
                        vecTime[k][2] = 10;
                    }
                }
            } else if (vecX1[j] + 1 == i) {
                for (int k = vecY1[j]; k <= vecY2[j]; ++k) {
                    if (k < vecY2[j]) {
                        vecTime[k][0] = vecT[j];
                    }
                    if (k > vecY1[j]) {
                        vecTime[k][2] = vecT[j];
                    }
                }
            }
        }
        for (int j = 0; j + 1 < m; ++j) {
            vecDist[j + 1] = min(vecDist[j + 1], vecDist[j] + vecTime[j][0] * (vecY[j + 1] - vecY[j]));
        }
        for (int j = m - 1; j > 0; --j) {
            vecDist[j - 1] = min(vecDist[j - 1], vecDist[j] + vecTime[j][2] * (vecY[j] - vecY[j - 1]));
        }

        if (xb == i) {
            mind = min(mind, vecDist[yb]);
            return;
        }
        vecD = vecDist;
    }
}

void Solve() {
    cin >> xa >> ya >> xb >> yb >> n;
    vecX1.resize(n), vecY1.resize(n), vecX2.resize(n), vecY2.resize(n), vecT.resize(n);
    vecX.push_back(xa), vecX.push_back(xb);
    vecY.push_back(ya), vecY.push_back(yb);
    for (int i = 0; i < n; ++i) {
        cin >> vecX1[i] >> vecY1[i] >> vecX2[i] >> vecY2[i] >> vecT[i];
        vecX.push_back(vecX1[i]), vecX.push_back(vecX2[i]);
        vecY.push_back(vecY1[i]), vecY.push_back(vecY2[i]);
    }
    sort(vecX.begin(), vecX.end());
    sort(vecY.begin(), vecY.end());
    vecX.erase(unique(vecX.begin(), vecX.end()), vecX.end());
    vecY.erase(unique(vecY.begin(), vecY.end()), vecY.end());
    xa = lower_bound(vecX.begin(), vecX.end(), xa) - vecX.begin();
    xb = lower_bound(vecX.begin(), vecX.end(), xb) - vecX.begin();
    ya = lower_bound(vecY.begin(), vecY.end(), ya) - vecY.begin();
    yb = lower_bound(vecY.begin(), vecY.end(), yb) - vecY.begin();
    for (int i = 0; i < n; ++i) {
        vecX1[i] = lower_bound(vecX.begin(), vecX.end(), vecX1[i]) - vecX.begin();
        vecX2[i] = lower_bound(vecX.begin(), vecX.end(), vecX2[i]) - vecX.begin();
        vecY1[i] = lower_bound(vecY.begin(), vecY.end(), vecY1[i]) - vecY.begin();
        vecY2[i] = lower_bound(vecY.begin(), vecY.end(), vecY2[i]) - vecY.begin();
    }
    mind = 1e18;
    Processing();
    swap(xa, ya), swap(xb, yb);
    swap(vecX1, vecY1), swap(vecX2, vecY2);
    swap(vecX, vecY);
    Processing();
    cout << mind;
}

int main() {
    Task();
    Solve();
}
