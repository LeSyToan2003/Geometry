#include <bits/stdc++.h>

using namespace std;

const int MOD = 2023;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

// Nhân hai ma trận A, B
vector <vector <int>> Mul(vector <vector <int>> vecA, vector <vector <int>> vecB) {
    int n = vecA.size() - 1;
    vector <vector <int>> vecAns(n + 1, vector <int> (n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                vecAns[i][j] = (vecAns[i][j] + vecA[i][k] * vecB[k][j] % MOD) % MOD;
            }
        }
    }

    return vecAns;
}

// Tính lũy thừa ma trận G^k
vector <vector <int>> Pow(vector <vector <int>> vecA, int k) {
    if (k == 1) {
        return vecA;
    }

    vector <vector <int>> vecB = Pow(vecA, k / 2);
    vector <vector <int>> vecAns = Mul(vecB, vecB);
    if (k % 2) {
        vecAns = Mul(vecAns, vecA);
    }

    return vecAns;
}

void Solve() {
    int n; cin >> n;
    vector <int> vecA(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> vecA[i];
    }

    // Xây dựng ma trận G ban đầu: G[i][j] = 1 nếu có cạnh
    vector <vector <int>> vecG(n + 1, vector <int> (n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (vecA[i] < vecA[j] && __gcd(vecA[i], vecA[j]) == 1) {
                vecG[i][j] = 1;
            }
        }
    }

    // In ra các ma trận G^k:
    for (int k = 1; k <= n; ++k) {
        cout << "Matrix G^" << k << ":\n";
        vector <vector <int>> vecGk = Pow(vecG, k);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << vecGk[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int main() {
    Task();
    Solve();
}
